#!/usr/bin/env python3
"""Serve the local browser build, including its precompressed WASM and assets."""
import argparse
from functools import partial
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path


class Handler(SimpleHTTPRequestHandler):
    def send_head(self):
        file = Path(self.translate_path(self.path))
        compressed = file.with_suffix(file.suffix + '.gz')
        if file.is_file() and compressed.is_file() and 'gzip' in self.headers.get('Accept-Encoding', ''):
            self.send_response(200)
            self.send_header('Content-Type', self.guess_type(str(file)))
            self.send_header('Content-Encoding', 'gzip')
            self.send_header('Vary', 'Accept-Encoding')
            self.send_header('Content-Length', str(compressed.stat().st_size))
            self.end_headers()
            return compressed.open('rb')
        return super().send_head()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--port', type=int, default=8080)
    parser.add_argument('--bind', default='127.0.0.1')
    parser.add_argument('--directory', type=Path, default=Path(__file__).resolve().parents[1] / 'build-web')
    args = parser.parse_args()
    if not (args.directory / 'index.html').is_file():
        parser.error('Build the browser version first with scripts/build-web.sh')
    server = ThreadingHTTPServer((args.bind, args.port), partial(Handler, directory=str(args.directory)))
    print(f'DeathWard: http://{args.bind}:{server.server_port}', flush=True)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        server.server_close()
