PATH_TO_LATEST_JPG = "/run/shm/1.jpg"
CAPTURE_COMMAND = ["/usr/bin/raspistill", "-t", "200", "-n", "-w", "800", "-h", "600", "-vf", "-o", "/run/shm/1.jpg"]
MINIMUM_TIME_BETWEEN_CAPTURES = 5  # seconds
JSREFRESH = MINIMUM_TIME_BETWEEN_CAPTURES * 1000
LOCKFILE = "/run/shm/raspistill_http.last"
INDEX_HTML = """
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <title>RaspiStill_HTTP Index</title>
  </head>
  <body>
    <h1>Camera</h1>
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

