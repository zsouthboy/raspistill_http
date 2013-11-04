PATH_TO_LATEST_JPG = "/run/shm/1.jpg"
RASPISTILL_LOCKFILE = "/run/shm/raspistill.lck"
RASPISTILL_PIDFILE = "/run/shm/raspistill.pid"
# vertically flipping the image by default, remove -vf if you don't need it
RASPISTILL_DAEMON = ['bin/daemonize', '-l', RASPISTILL_LOCKFILE, '-p', RASPISTILL_PIDFILE, '-c', '/run/shm/', '/usr/bin/raspistill', '-t', '2147483647', '-vf', '-tl', '1000', '-n', '-o', PATH_TO_LATEST_JPG, '-w', '800', '-h', '600', '-q', '35']
JSREFRESH = 1000
INDEX_HTML = """
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <title>RaspiStill_HTTP Index</title>
  </head>
  <body>
    <h1>raspistill_http Pi Camera</h1>
    <img src="/jpg" id="webcam_view">
    <script>
    var im = document.getElementById("webcam_view");
    var chimg = function(){{
        im.src = "/jpg?rand=" + Math.random();
        setTimeout(chimg, {0});
    }};
    setTimeout(chimg, {0});
    </script>
  </body>
</html>

""".format(JSREFRESH)

