from flask import Flask
from flask import Markup
from flask import Flask
from flask import render_template

app = Flask(__name__)


@app.route("/")
def home():
    labels = ["January", "February", "March", "April", "May", "June", "July", "August"]
    values = [10, 9, 8, 7, 6, 4, 7, 8]
    return render_template('line_chart.html', values=values, labels=labels)


if __name__ == "__main__":
    app.run(host='192.168.2.111', port=80, debug=True)
