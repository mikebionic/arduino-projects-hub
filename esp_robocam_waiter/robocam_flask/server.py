from flask import Flask, render_template, make_response
import requests

app = Flask("__main__")

robo_url = "http://192.168.43.5"

@app.route("/control/<command>")
def turn_on(command):
    print(command)
    r = requests.get("{}/{}".format(robo_url, command))
    print(r.text)
    return make_response("ok")

@app.route("/camera/")
def camera():
    return render_template("/robocam.html")


if __name__ == "__main__":
    app.run("0.0.0.0")
