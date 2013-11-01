#!/usr/bin/python
import web
import sys
import subprocess
from const import *
import time

urls = (
    "/", "index",
    "/jpg", "jpg"
)
# HACK. ugh
LAST_CAPTURE = time.time() - MINIMUM_TIME_BETWEEN_CAPTURES


class index:
    def GET(self):
        return INDEX_HTML


class jpg:
    def GET(self):
        # HACK
        global LAST_CAPTURE
	if time.time() > (LAST_CAPTURE + MINIMUM_TIME_BETWEEN_CAPTURES):
                subprocess.call(CAPTURE_COMMAND)
                LAST_CAPTURE = time.time()
        web.header("Content-Type", "image/jpeg")
        out = open(PATH_TO_LATEST_JPG, "rb").read()
        return out


if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()

