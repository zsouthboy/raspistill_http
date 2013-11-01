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


class index:
    def GET(self):
        return INDEX_HTML


class jpg:
    def __init__(self):
        self.last_capture = 0

    def GET(self):
	if time.time() > (self.last_capture + MINIMUM_TIME_BETWEEN_CAPTURES):
                subprocess.call(CAPTURE_COMMAND)
                self.last_capture = time.time()
        web.header("Content-Type", "image/jpeg")
        out = open(PATH_TO_LATEST_JPG, "rb").read()
        return out


if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()

