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
        start_daemon() 
        return INDEX_HTML


class jpg:
    def GET(self):
        web.header("Content-Type", "image/jpeg")
        return get_image()

def get_image():
    if not os.path.exists(RASPISTILL_PIDFILE):
        start_daemon()
        # sleep to allow first image to be captured
        sleep(2)
    img = open(PATH_TO_LATEST_JPG, "rb").read()
    return img

def start_daemon():
    # safe to call multiple times, daemonize will prevent more than one at a time
    res = subprocess.call(RASPISTILL_DAEMON)
    return res

if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()

