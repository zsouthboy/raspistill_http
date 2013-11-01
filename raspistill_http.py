#!/usr/bin/python
import web
import sys
import subprocess
from const import *
import time
import os.path

urls = (
    "/", "index",
    "/jpg", "jpg"
)


class index:
    def GET(self):
        return INDEX_HTML


class jpg:
    def GET(self):
        # that's right, read the entire file every time. it's in ram, it'll be ok
	if ok_to_capture():
                subprocess.call(CAPTURE_COMMAND)
                open(LOCKFILE, "w").write(str(time.time()))
        web.header("Content-Type", "image/jpeg")
        out = open(PATH_TO_LATEST_JPG, "rb").read()
        return out

def ok_to_capture():
    if not os.path.exists(LOCKFILE):
        open(LOCKFILE, "w").write(str(time.time()))
    # same, he's in ram, we're not killing the poor raspberry pi sdcard
    if time.time() > (float(open(LOCKFILE).read()) + MINIMUM_TIME_BETWEEN_CAPTURES):
        return True
    return False

if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()

