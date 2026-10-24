#!/usr/bin/env python3
"""Render the persistent Isaac study as an offline HTML report.

Requires markdown-it-py only at generation time; the HTML has no external assets.
"""

from collections import Counter
from html import escape
import hashlib
import os
from pathlib import Path
import re
from urllib.parse import quote, unquote, urlsplit, urlunsplit

from markdown_it import MarkdownIt


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / 'docs/isaac_expedition_study.md'
OUTPUT = ROOT / 'docs/reports/isaac-expedition-study-2026-10-24.html'

CSS = """
:root { color-scheme: light; --ink:#202e37; --muted:#52646f; --line:#d8e1e5; --accent:#176375; }
* { box-sizing:border-box; }
html { scroll-behavior:smooth; }
body { margin:0; background:#edf1f3; color:var(--ink); font:16px/1.65 system-ui,sans-serif; }
.layout { display:grid; grid-template-columns:240px minmax(0,1080px); gap:30px; max-width:1420px; margin:32px auto; padding:0 24px; }
nav { position:sticky; top:24px; align-self:start; max-height:calc(100vh - 48px); overflow:auto; font-size:13px; padding:16px 0; }
nav strong { display:block; margin-bottom:14px; letter-spacing:.08em; text-transform:uppercase; }
nav ol { padding-left:20px; }
nav li { padding:5px 0; }
main { min-width:0; padding:36px 48px; background:white; border:1px solid var(--line); border-radius:12px; }
h1,h2,h3 { line-height:1.25; scroll-margin-top:24px; }
h1 { font-size:36px; margin-top:0; letter-spacing:-.025em; }
h2 { font-size:26px; margin:48px 0 20px; border-top:2px solid var(--line); padding-top:24px; }
h3 { font-size:19px; margin:30px 0 12px; }
a { color:var(--accent); text-decoration-thickness:1px; text-underline-offset:3px; overflow-wrap:anywhere; }
p { margin:14px 0; }
li { margin:7px 0; }
code { font-size:.87em; background:#edf3f5; padding:2px 4px; border-radius:3px; overflow-wrap:anywhere; }
pre { padding:18px; background:#152c37; color:#e8f2f5; border-radius:6px; overflow:auto; }
pre code { background:transparent; padding:0; color:inherit; }
.table-wrap { overflow-x:auto; margin:22px 0; }
table { border-collapse:collapse; width:100%; font-size:13px; line-height:1.5; }
th,td { padding:12px; border:1px solid var(--line); vertical-align:top; min-width:90px; }
th { background:#e7f0f3; text-align:left; }
tbody tr:nth-child(even) { background:#f7f9fa; }
blockquote { margin:20px 0; border-left:4px solid var(--accent); padding:6px 18px; background:#eef6f7; }
footer { margin-top:36px; padding-top:16px; border-top:1px solid var(--line); color:var(--muted); font-size:12px; overflow-wrap:anywhere; }
@media(max-width:950px) { .layout { display:block; padding:0 12px; margin:12px auto; } nav { position:static; max-height:none; padding:12px; } main { padding:24px; } h1 { font-size:29px; } }
@media print { @page { size:A4; margin:14mm; } body { background:white; font-size:10pt; } .layout { display:block; margin:0; padding:0; } nav { display:none; } main { border:0; padding:0; } h1 { font-size:24pt; } h2 { font-size:17pt; } h3 { font-size:12pt; } h1,h2,h3 { break-after:avoid; } table { font-size:8pt; } th,td { min-width:0; padding:6px; } tr { break-inside:avoid; } thead { display:table-header-group; } pre { white-space:pre-wrap; overflow-wrap:anywhere; } .table-wrap { overflow:visible; } a { color:inherit; } }
"""


def main():
    source = SOURCE.read_text(encoding='utf-8')
    md = MarkdownIt('commonmark', {'html': False}).enable('table')
    tokens = md.parse(source)
    headings, ids = [], Counter()
    for index, token in enumerate(tokens):
        if token.type == 'heading_open':
            label = tokens[index + 1].content
            slug = re.sub(r'[^a-z0-9]+', '-', label.lower()).strip('-')
            ids[slug] += 1
            if ids[slug] > 1:
                slug += '-' + str(ids[slug])
            token.attrSet('id', slug)
            if token.tag == 'h2':
                headings.append((slug, label))
        for child in token.children or []:
            if child.type != 'link_open':
                continue
            url = urlsplit(child.attrGet('href'))
            if not url.scheme and not url.netloc and url.path:
                target = SOURCE.parent / unquote(url.path)
                relative = Path(os.path.relpath(target, OUTPUT.parent)).as_posix()
                child.attrSet('href', urlunsplit(('', '', quote(relative, safe='/'), url.query, url.fragment)))
    body = md.renderer.render(tokens, md.options, {})
    body = body.replace('<table>', '<div class="table-wrap"><table>').replace('</table>', '</table></div>')
    toc = ''.join(f'<li><a href="#{slug}">{escape(label)}</a></li>' for slug, label in headings)
    digest = hashlib.sha256(SOURCE.read_bytes()).hexdigest()
    document = f'''<!doctype html>
<html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<meta name="source-sha256" content="{digest}"><title>Isaac mechanics and DeathWard expedition design</title>
<style>{CSS}</style></head><body><div class="layout">
<nav aria-label="Report contents"><strong>DeathWard research</strong><ol>{toc}</ol>
<p><a href="../isaac_expedition_study.md">Markdown source</a></p><p>Offline report · 24 October 2026<br>Use your browser's Print command to save a PDF.</p></nav>
<main>{body}<footer>Generated from docs/isaac_expedition_study.md.<br>Source SHA-256: {digest}</footer></main>
</div></body></html>
'''
    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    OUTPUT.write_text(document, encoding='utf-8')
    print(OUTPUT.relative_to(ROOT))


if __name__ == '__main__':
    main()
