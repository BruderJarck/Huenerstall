#!/usr/bin/env python
import time

from flask import Flask, render_template
from flask_mobility import Mobility
from flask_mobility.decorators import mobile_template

app = Flask(__name__)
Mobility(app)
labels = ["January", "February", "March", "April", "May", "June", "July", "August"]
values = [10, 9, 8, 7, 6, 4, 7, 8]

@app.route('/')
@mobile_template('{mobile/}index.html')
def index(template):
    template_data = {
        'title': 'OpenHennery webinterface',
        'time_received': "ja heute halt",
        'door_state': "ha offa",
        'bat_voltage': "mehrere kilovölter",
        'labels': ["January", "February", "March", "April", "May", "June", "July", "August"],
        'values': [10, 9, 8, 7, 6, 4, 7, 8]
    }
    return render_template(template, **template_data)


if __name__ == '__main__':
    app.run(host='192.168.2.111', port=80,debug=True)

