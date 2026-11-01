#!/usr/bin/env python3
"""Download the Isaac wiki Monsters page and every monster page it links to.

Scope is deliberately narrow: the `Monsters` and `Champions` overview articles, the monster pages linked from
its Monster List and Monster Replacement tables, and the sprite images those pages
embed. Nothing else (no site chrome, scripts, ads, navboxes, other wiki sections).

Fandom fronts its HTML pages with a Cloudflare JavaScript challenge, so this script
reads rendered article HTML through the MediaWiki API (api.php?action=parse), which
is not challenged. The image CDN rejects some browser user agents, so images are
requested with a plain one and `format=original` to get the real PNG rather than a
negotiated WebP.

Output layout (default docs/reports/isaac-wiki/monsters/):
  Monsters.html         standalone index page, links rewritten to local pages
  Champions.html        champion overview page, links rewritten the same way
  pages/<Title>.html    one standalone page per monster article
  images/<file>         sprite images embedded by those pages
  manifest.json         provenance: source URL, revision id, redirects, failures
  .cache/api/*.json     raw API responses (lets a rerun resume without refetching)
"""
from __future__ import annotations

import argparse
import concurrent.futures
import html
import json
import re
import sys
import threading
import time
import urllib.error
import urllib.parse
import urllib.request
from pathlib import Path

from bs4 import BeautifulSoup

WIKI = "https://bindingofisaacrebirth.fandom.com"
API = WIKI + "/api.php"
START_PAGE = "Monsters"
# Extra top-level overview pages kept beside Monsters.html; their links point into pages/.
# Monster pages are discovered from the Monsters tables only, never from these.
TOP_PAGES = [START_PAGE, "Champions"]
# api.php accepts a normal browser UA; the static image CDN (Varnish) returns 403 for
# partial Chrome-looking UAs but serves a bare Mozilla token fine.
API_UA = ("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) "
          "Chrome/130.0 Safari/537.36")
IMG_UA = "Mozilla/5.0"
ROOT = Path(__file__).resolve().parents[2]
DEFAULT_OUT = ROOT / "docs/reports/isaac-wiki/monsters"

STYLE = """
body{font-family:system-ui,sans-serif;max-width:1100px;margin:1.5rem auto;padding:0 1rem;
 background:#fff;color:#111;line-height:1.45}
.source{font-size:.85rem;color:#555;border-bottom:1px solid #ddd;padding-bottom:.5rem;margin-bottom:1rem}
table.wikitable{border-collapse:collapse;margin:.75rem 0}
table.wikitable th,table.wikitable td{border:1px solid #bbb;padding:.3rem .5rem;vertical-align:top}
table.wikitable th{background:#eee}
.striped tr:nth-child(even){background:#f7f7f7}
img{max-width:100%;height:auto}
.inline-icon img{vertical-align:middle}
.infobox,.portable-infobox{float:right;max-width:320px;margin:0 0 1rem 1rem;border:1px solid #ccc;
 padding:.5rem;background:#fafafa;font-size:.9rem}
.thumb{display:inline-block;margin:.25rem}
.mw-collapsible-toggle{display:none}
@media (prefers-color-scheme:dark){body{background:#151515;color:#eee}table.wikitable th{background:#333}
 .striped tr:nth-child(even){background:#202020}table.wikitable th,table.wikitable td{border-color:#555}
 .infobox,.portable-infobox{background:#1e1e1e;border-color:#444}a{color:#8ab4f8}}
"""


class Fetcher:
    """Polite HTTP client: one request at a time per host, pacing, retries with backoff."""

    def __init__(self, delay: float):
        self.delay = delay
        self.lock = threading.Lock()
        self.last = 0.0

    def get(self, url: str, ua: str, retries: int = 4) -> bytes:
        for attempt in range(retries):
            with self.lock:
                wait = self.delay - (time.monotonic() - self.last)
                if wait > 0:
                    time.sleep(wait)
                self.last = time.monotonic()
            req = urllib.request.Request(url, headers={"User-Agent": ua, "Accept": "*/*"})
            try:
                with urllib.request.urlopen(req, timeout=60) as resp:
                    return resp.read()
            except urllib.error.HTTPError as err:
                if err.code in (403, 404) and attempt == retries - 1:
                    raise
                if err.code in (404,):
                    raise
                backoff = 2.0 * (attempt + 1)
                print(f"  retry {attempt + 1} after HTTP {err.code} ({backoff:.0f}s): {url}", file=sys.stderr)
                time.sleep(backoff)
            except (urllib.error.URLError, TimeoutError) as err:
                backoff = 2.0 * (attempt + 1)
                print(f"  retry {attempt + 1} after {err} ({backoff:.0f}s): {url}", file=sys.stderr)
                time.sleep(backoff)
        raise RuntimeError(f"gave up on {url}")


def slug(title: str) -> str:
    """File-system safe name that stays readable (Keeper_(Enemy) -> Keeper_(Enemy))."""
    title = title.replace(" ", "_")
    return re.sub(r"[^A-Za-z0-9._()'+,-]", "_", title)


def api_parse(fetcher: Fetcher, cache: Path, title: str) -> dict:
    key = cache / (slug(title) + ".json")
    if key.exists():
        return json.loads(key.read_text())
    params = {
        "action": "parse", "page": title, "redirects": 1, "format": "json", "formatversion": 2,
        "prop": "text|revid|displaytitle|categories",
        "disableeditsection": 1, "disabletoc": 1,
    }
    data = fetcher.get(API + "?" + urllib.parse.urlencode(params), API_UA)
    result = json.loads(data)
    if "error" in result:
        raise ValueError(f"{title}: {result['error']}")
    key.parent.mkdir(parents=True, exist_ok=True)
    key.write_text(json.dumps(result, ensure_ascii=False))
    return result


def api_redirects_to(fetcher: Fetcher, cache: Path, title: str) -> list[str]:
    """Titles that redirect to `title` (e.g. Champion -> Champions), so links to them stay local."""
    key = cache / f"_redirects_to_{slug(title)}.json"
    if key.exists():
        return json.loads(key.read_text())
    params = {"action": "query", "prop": "redirects", "titles": title, "rdlimit": "max",
              "format": "json", "formatversion": 2}
    result = json.loads(fetcher.get(API + "?" + urllib.parse.urlencode(params), API_UA))
    names = [r["title"] for page in result.get("query", {}).get("pages", []) for r in page.get("redirects", [])]
    key.parent.mkdir(parents=True, exist_ok=True)
    key.write_text(json.dumps(names, ensure_ascii=False))
    return names


def wiki_title(href: str) -> str | None:
    """'/wiki/Keeper_(Enemy)#Section' -> 'Keeper_(Enemy)'; None for non-article links."""
    if not href.startswith("/wiki/"):
        return None
    title = urllib.parse.unquote(href[len("/wiki/"):].split("#")[0].split("?")[0])
    if not title or ":" in title:  # File:, Category:, Special:, Template: ...
        return None
    return title


def monster_titles(soup: BeautifulSoup) -> list[str]:
    """Monster pages linked from the Monster List and Monster Replacement tables."""
    titles: list[str] = []

    def collect(cells):
        for td in cells:
            for a in td.find_all("a", href=True):
                t = wiki_title(a["href"])
                if t and t not in titles:
                    titles.append(t)

    for table in soup.find_all("table"):
        headers = [th.get_text(strip=True) for th in table.find_all("th")]
        if not headers:
            continue
        if headers[0] == "Entity":  # Monster List: Entity | ID | Description
            for row in table.find_all("tr")[1:]:
                tds = row.find_all("td")
                if tds:
                    collect([tds[0]])
        elif headers[0] == "Base Monster":  # Replacements: Base Monster | Replacement | ...
            for row in table.find_all("tr")[1:]:
                collect(row.find_all("td")[:2])
    return titles


def sort_monster_list_by_id(soup: BeautifulSoup) -> int:
    """Reorder the Monster List table rows by entity ID (type.variant.subtype, numeric).

    The wiki groups rows by monster family; sorting by ID makes lookups by entity ID direct.
    Returns the number of rows sorted."""
    def id_key(row):
        text = row.find_all("td")[1].get_text(strip=True)
        parts = [int(p) if p.isdigit() else 0 for p in text.split(".")]
        return tuple(parts + [0] * (3 - len(parts)))

    sorted_rows = 0
    for table in soup.find_all("table"):
        first = table.find("th")
        if not first or first.get_text(strip=True) != "Entity":
            continue
        body = table.find("tbody") or table
        rows = [r for r in body.find_all("tr", recursive=False) if len(r.find_all("td")) >= 2]
        for row in rows:
            row.extract()
        for row in sorted(rows, key=id_key):
            body.append(row)
        sorted_rows += len(rows)
    return sorted_rows


def original_image_url(src: str) -> str | None:
    if not src or src.startswith("data:"):
        return None
    if "static.wikia.nocookie.net" not in src:
        return None
    base = src.split("/revision/")[0]
    return base + "/revision/latest?format=original"


def image_filename(img) -> str:
    key = img.get("data-image-key")
    if key:
        return slug(urllib.parse.unquote(key))
    src = img.get("data-src") or img.get("src") or ""
    name = src.split("/revision/")[0].rsplit("/", 1)[-1]
    return slug(urllib.parse.unquote(name)) or "image"


class Builder:
    def __init__(self, out: Path, fetcher: Fetcher, image_fetcher: Fetcher):
        self.out = out
        self.fetcher = fetcher
        self.image_fetcher = image_fetcher
        self.images: dict[str, str] = {}  # local filename -> source url
        self.local_pages: dict[str, str] = {}  # wiki title (incl. redirects) -> slug of resolved page

    def rewrite(self, content: BeautifulSoup, page_dir_prefix: str, image_prefix: str) -> None:
        for tag in content.find_all(["script", "style", "noscript"]):
            tag.decompose()
        for tag in content.select(".mw-editsection, .navbox, .nav-box, .nomobile.navbox, #toc, .toc, .noprint"):
            tag.decompose()
        for a in content.find_all("a", href=True):
            href = a["href"]
            title = wiki_title(href)
            fragment = "#" + href.split("#", 1)[1] if "#" in href else ""
            if title and title in self.local_pages:
                a["href"] = f"{page_dir_prefix}{self.local_pages[title]}.html{fragment}"
            elif href.startswith("/"):
                a["href"] = WIKI + href
            elif href.startswith("//"):
                a["href"] = "https:" + href
        for img in content.find_all("img"):
            src = img.get("data-src") or img.get("src") or ""
            url = original_image_url(src)
            for attr in ("srcset", "data-srcset", "data-src", "loading", "decoding"):
                if attr in img.attrs:
                    del img[attr]
            if not url:
                continue
            name = image_filename(img)
            self.images.setdefault(name, url)
            img["src"] = f"{image_prefix}{name}"
        for span in content.find_all("span", typeof="mw:File"):
            a = span.find("a", href=True)
            if a and a["href"].startswith(WIKI + "/wiki/File:"):
                a.unwrap()

    def write_page(self, path: Path, title: str, source: str, revid, content_html: str) -> None:
        doc = (
            "<!DOCTYPE html>\n<html lang=\"en\"><head><meta charset=\"utf-8\">\n"
            f"<title>{html.escape(title)} - Binding of Isaac: Rebirth Wiki (monsters mirror)</title>\n"
            f"<style>{STYLE}</style></head><body>\n"
            f"<div class=\"source\">Source: <a href=\"{source}\">{source}</a> "
            f"(revision {revid}, fetched {time.strftime('%Y-%m-%d')}). "
            "Text is CC BY-SA 3.0 from the Binding of Isaac: Rebirth Wiki on Fandom.</div>\n"
            f"<h1>{html.escape(title)}</h1>\n{content_html}\n</body></html>\n"
        )
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(doc, encoding="utf-8")

    def download_images(self, workers: int) -> tuple[int, list[dict]]:
        img_dir = self.out / "images"
        img_dir.mkdir(parents=True, exist_ok=True)
        todo = [(n, u) for n, u in self.images.items() if not (img_dir / n).exists()]
        failures: list[dict] = []
        done = 0

        def grab(item):
            name, url = item
            try:
                data = self.image_fetcher.get(url, IMG_UA)
                if data[:15].lower().startswith(b"<!doctype html") or data[:5] == b"<html":
                    raise RuntimeError("CDN returned HTML instead of an image")
                (img_dir / name).write_bytes(data)
                return name, None
            except Exception as err:  # noqa: BLE001 - record and continue
                return name, str(err)

        with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as pool:
            for i, (name, err) in enumerate(pool.map(grab, todo), 1):
                if err:
                    failures.append({"image": name, "url": self.images[name], "error": err})
                else:
                    done += 1
                if i % 100 == 0 or i == len(todo):
                    print(f"  images {i}/{len(todo)} ({len(failures)} failed)")
        return done, failures


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--out", type=Path, default=DEFAULT_OUT)
    ap.add_argument("--delay", type=float, default=0.6, help="seconds between requests")
    ap.add_argument("--image-delay", type=float, default=0.2, help="seconds between image requests")
    ap.add_argument("--image-workers", type=int, default=3)
    ap.add_argument("--skip-images", action="store_true")
    args = ap.parse_args()

    out: Path = args.out
    cache = out / ".cache" / "api"
    fetcher = Fetcher(args.delay)
    builder = Builder(out, fetcher, Fetcher(args.image_delay))

    print(f"[1/4] fetching {', '.join(TOP_PAGES)} via API")
    top = {name: api_parse(fetcher, cache, name)["parse"] for name in TOP_PAGES}
    index = top[START_PAGE]
    index_soup = BeautifulSoup(index["text"], "lxml")
    titles = monster_titles(index_soup)
    print(f"      {len(titles)} monster links found in the Monster List / Replacement tables")

    print(f"[2/4] fetching {len(titles)} monster pages")
    pages: dict[str, dict] = {}  # resolved title -> parse result
    redirects: dict[str, str] = {}
    failures: list[dict] = []
    for i, title in enumerate(titles, 1):
        try:
            parsed = api_parse(fetcher, cache, title)["parse"]
        except Exception as err:  # noqa: BLE001
            failures.append({"page": title, "error": str(err)})
            print(f"  {i:3}/{len(titles)} FAILED {title}: {err}")
            continue
        resolved = parsed["title"]
        if resolved != title.replace("_", " "):
            redirects[title] = resolved
        if resolved not in pages:
            pages[resolved] = parsed
            print(f"  {i:3}/{len(titles)} {title}" + (f" -> {resolved}" if title in redirects else ""))
        else:
            print(f"  {i:3}/{len(titles)} {title} -> {resolved} (already fetched)")

    for resolved in pages:
        builder.local_pages[resolved.replace(" ", "_")] = slug(resolved)
        builder.local_pages[resolved] = slug(resolved)
    for alias, resolved in redirects.items():
        builder.local_pages[alias] = slug(resolved)
    for name in TOP_PAGES:  # links from monster pages back to the overview pages, incl. redirects
        builder.local_pages[name] = name
        for alias in api_redirects_to(fetcher, cache, name):
            builder.local_pages[alias] = name
            builder.local_pages[alias.replace(" ", "_")] = name

    print("[3/4] writing standalone HTML")
    pages_dir = out / "pages"
    manifest_pages = []
    for resolved, parsed in sorted(pages.items()):
        soup = BeautifulSoup(parsed["text"], "lxml")
        content = soup.find("div", class_="mw-parser-output") or soup
        builder.rewrite(content, page_dir_prefix="", image_prefix="../images/")
        # the overview pages live one directory up from pages/
        for a in content.find_all("a", href=True):
            if any(a["href"].startswith(f"{name}.html") for name in TOP_PAGES):
                a["href"] = "../" + a["href"]
        source = f"{WIKI}/wiki/{urllib.parse.quote(resolved.replace(' ', '_'))}"
        path = pages_dir / f"{slug(resolved)}.html"
        builder.write_page(path, resolved, source, parsed.get("revid"), str(content))
        manifest_pages.append({
            "title": resolved, "file": str(path.relative_to(out)), "source": source,
            "revid": parsed.get("revid"),
            "redirected_from": sorted(a for a, r in redirects.items() if r == resolved),
            "categories": [c["category"] for c in parsed.get("categories", [])],
        })

    print(f"      Monster List rows sorted by entity ID: {sort_monster_list_by_id(index_soup)}")
    manifest_top = []
    for name, parsed in top.items():
        soup = index_soup if name == START_PAGE else BeautifulSoup(parsed["text"], "lxml")
        content = soup.find("div", class_="mw-parser-output") or soup
        builder.rewrite(content, page_dir_prefix="pages/", image_prefix="images/")
        builder.write_page(out / f"{name}.html", name, f"{WIKI}/wiki/{name}", parsed.get("revid"), str(content))
        manifest_top.append({"title": name, "file": f"{name}.html", "source": f"{WIKI}/wiki/{name}",
                             "revid": parsed.get("revid")})

    image_failures: list[dict] = []
    downloaded = 0
    if args.skip_images:
        print(f"[4/4] skipping {len(builder.images)} images")
    else:
        print(f"[4/4] downloading {len(builder.images)} sprite images")
        downloaded, image_failures = builder.download_images(args.image_workers)

    manifest = {
        "source": f"{WIKI}/wiki/{START_PAGE}",
        "fetched_utc": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
        "method": "MediaWiki API action=parse (HTML pages are behind a Cloudflare challenge)",
        "index": {"file": f"{START_PAGE}.html", "revid": index.get("revid")},
        "top_pages": manifest_top,
        "linked_titles": titles,
        "pages": manifest_pages,
        "redirects": redirects,
        "images": {"referenced": len(builder.images), "downloaded_this_run": downloaded,
                   "present": len(list((out / "images").glob("*"))) if (out / "images").exists() else 0},
        "failures": {"pages": failures, "images": image_failures},
    }
    (out / "manifest.json").write_text(json.dumps(manifest, indent=2, ensure_ascii=False) + "\n")
    print(f"done: {len(top)} overview pages, {len(pages)} monster pages, {len(redirects)} redirects, {len(failures)} page failures, "
          f"{len(image_failures)} image failures -> {out}")
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
