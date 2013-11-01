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
        web.header("Content-Type", "image/jpeg")
        return get_image()

def ok_to_capture():
    # that's right, read the entire file every time. it's in ram, it'll be ok
    # we're not killing the poor raspberry pi sdcard
    if not os.path.exists(LOCKFILE):
        open(LOCKFILE, "w").write(str(time.time()))
        True
    if time.time() > (float(open(LOCKFILE).read()) + MINIMUM_TIME_BETWEEN_CAPTURES):
        return True
    return False


def get_image():
    if ok_to_capture():
        open(LOCKFILE, "w").write(str(time.time()))
        res = subprocess.call(CAPTURE_COMMAND)
        if res != 0:
            return "DEADBEEF"
    img = open(PATH_TO_LATEST_JPG, "rb").read()
    return img

if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()

