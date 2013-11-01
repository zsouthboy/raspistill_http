#!/usr/bin/python
import web
import sys
import subprocess
from const import *

urls = (
    "/", "index",
    "/jpg", "jpg"
)


class index:
    def GET(self):
        return INDEX_HTML


class jpg:
    def GET(self):
        subprocess.call(CAPTURE_COMMAND)
        web.header("Content-Type", "image/jpeg")
        out = open(PATH_TO_LATEST_JPG, "rb").read()
        return out


if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()

