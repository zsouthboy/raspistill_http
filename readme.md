Raspistill_http
===============

A simple python script using `web.py` that serves images from a Raspberry Pi with Rasberry Pi Camera, like a webcam might. The Pi Camera has much higher quality images compared to ip webcams, but you're not getting 15fps as a tradeoff.
Uses `daemonize` from http://software.clapper.org/daemonize/, a compiled copy is in the bin directory.
`raspistill` doesn't have a built-in run forever daemon mode, so it's launched with `daemonize` and the appropriate arguments to run for 24d before exiting, after which it will be relaunched for another 24d at the next browsing of the page.
A simple javascript function refreshes the image in your webbrowser, or use an IP Camera app on your mobile device to watch your Pi Camera.
Intermediate files are written to RAM filesystem and not your sdcard.

Installation on Raspbian
------------------------
* Install `web.py` from apt
`sudo apt-get install python-webpy`
* clone this repository
`git clone https://github.com/zsouthboy/raspistill_http.git` 

Usage
-----
* Run
`./raspistill_http.py` 
* Then browse to [your raspberry pi's IP]:8080
* You can point your favorite IP Cam app at /jpg which will have the latest captured image each time it's refreshed
* Run with `nohup` or `screen` to keep webserver running after disconnecting if you'd like, or put it in an init script

License
-------
Released into public domain

