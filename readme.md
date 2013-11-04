Raspistill_http
===============

![screenshot](https://raw.github.com/zsouthboy/raspistill_http/master/screenshot.png "screenshot of webui")

A simple python script using `web.py` that serves images from a Raspberry Pi with Rasberry Pi Camera, like a webcam might.

The Pi Camera has much higher quality images compared to cheap ip webcams.

Uses `daemonize` from http://software.clapper.org/daemonize/, a compiled copy is in the bin directory.

`raspistill` doesn't have a built-in run forever daemon mode, so it's launched with `daemonize` and the appropriate arguments to run for 24d (2147483647ms, its maximum) before exiting, after which it will be relaunched for another 24d.
A simple javascript function refreshes the image in your browser, or use an IP Camera app on your mobile device to watch your Pi Camera.
Intermediate files are written to RAM filesystem and not your sdcard to prevent unnecessary wear.

Installation on Raspbian
------------------------
* Make sure `raspistill` already works on your Pi

* Install `web.py` from default repos

`sudo apt-get install python-webpy`

* clone this repo

`git clone https://github.com/zsouthboy/raspistill_http.git` 

Usage
-----
* Simply run `./raspistill_http.py` in a terminal
* Browse to http://[your raspberry pi's IP]:8080
* You can point your favorite IP Cam app at [your raspberry pi's IP]:8080/jpg which will have the latest captured image each time it's refreshed
* Run with `nohup` or `screen` to keep webserver running after disconnecting if you'd like, or put it in an init script

License
-------
Released into public domain

