INDEX_HTML = """
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <title>RaspiStill_HTTP Index</title>
  </head>
  <body>
    <h1>Camera</h1>
    <img src="/jpg">
  </body>
</html>

"""

PATH_TO_LATEST_JPG = "/run/shm/1.jpg"
CAPTURE_COMMAND = "raspistill -t 500 -n -w 800 -h 600 -vf -o /run/shm/1.jpg"

