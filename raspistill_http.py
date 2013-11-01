#!/usr/bin/python
import web
import sys
from const import *

urls = (
    "/", "index"
)

class index:
    def GET(self):
        return INDEX_HTML

if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()

