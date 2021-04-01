import csv
from datetime import datetime
from flask import Flask, render_template, Response
import paho.mqtt.client as mqtt
import json
import base64

from flask_mobility import Mobility
from flask_mobility.decorators import mobile_template

APPEUI = '70B3D57ED001A086'
APPID = 'tempsens71263'
PSW = 'ttn-account-v2.6p1nkE0mLVt8YrtlAwJaWZixMQgHmc3jwdBd4ozDulw'

app = Flask(__name__)
Mobility(app)

payload = ["none received yet", 0, 0]
j_msg = {"metadata": {"time": 100}}
labels = []
values = []
fieldnames = ["time", "voltage"]

@app.route('/')
@mobile_template('{mobile/}index.html')
def index(template):
    template_data = {
        'title': 'OpenHennery webinterface',
        'time_received': j_msg["metadata"]["time"],
        'door_state': str(payload[0]),
        'zaun_state': str(payload[1]),
        'bat_voltage': str(int(payload[2]) / 10),
        'labels': labels,
        'values': values,
    }
    return render_template(template, **template_data)


def on_connect(client, userdata, flags, rc):
    global payload, j_msg, values, labels
    client.subscribe('+/devices/+/up'.format(APPEUI))
    with open("data.csv", "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            labels += [row["time"]]
            values += [row["voltage"]]


def on_message(client, userdata, msg):
    global payload, j_msg, values, labels
    j_msg = json.loads(msg.payload.decode('utf-8'))
    payload = base64.b64decode(j_msg['payload_raw'])
    labels += [str(datetime.now())]
    values += [int(payload[2])/10]

    with open("data.csv", "w") as file:
        writer = csv.DictWriter(file, fieldnames)
        writer.writerow({"time": labels[-1], "voltage": values[-1]})

ttn_client = mqtt.Client()
ttn_client.on_connect = on_connect
ttn_client.on_message = on_message
ttn_client.username_pw_set(APPID, PSW)
ttn_client.connect("eu.thethings.network", 1883, 60)  # MQTT port over TLS
ttn_client.loop_start()

if __name__ == '__main__':
    with open("data.csv", "w") as file:
        writer = csv.DictWriter(file, fieldnames)
        writer.writeheader()

    app.run(host='192.168.2.111', port=80, debug=True)
