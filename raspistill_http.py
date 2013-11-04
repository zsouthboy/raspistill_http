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
	# only if you try to get the index are we going to see if raspistill is running
	# this'll need to be modified when we allow config via webgui
	# we've told daemonize to prevent double invocation via .lck file
	res = subprocess.call(RASPISTILL_DAEMON)
	if res != 0:
		return INDEX_HTML + "raspistill daemon was already running"
        return INDEX_HTML


class jpg:
    def GET(self):
        web.header("Content-Type", "image/jpeg")
        return get_image()

def get_image():
    img = open(PATH_TO_LATEST_JPG, "rb").read()
    return img

if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()

