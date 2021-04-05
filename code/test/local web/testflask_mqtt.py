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

logfile = "./log.txt"
datafile = "./data.csv"


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

    append_to_file(logfile, f"[subscribed] \t{datetime.now()}")


    with open("data.csv", "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            labels += [row["time"]]
            values += [row["voltage"]]

        append_to_file(logfile, f"[red data] \t{labels}\n{values}\nlen: {len(labels)}/{len(values)}")

    if len(labels) > 14 or len(values) > 14:
        while len(labels) > 14:
            labels.pop(0)

        while len(values) > 14:
            values.pop(0)

        append_to_file(logfile, f"[shortened] \tlen:labels/values: {len(labels)}/{len(values)}")


def on_message(client, userdata, msg):
    global payload, j_msg, values, labels
    j_msg = json.loads(msg.payload.decode('utf-8'))
    payload = base64.b64decode(j_msg['payload_raw'])

    append_to_file(logfile, f"[message received] \t{[f'{x}' for x in payload]}, {datetime.now()}")

    labels += [str(datetime.now())]
    values += [int(payload[2]) / 10]

    append_to_file(logfile, f"[extended lists] \t{[f'{x}' for x in payload]}")

    with open("data.csv", "w") as file:
        file.truncate()

    with open("data.csv", "w") as file:
        writer = csv.DictWriter(file, fieldnames)
        writer.writeheader()
        for row in range(len(labels)):
            writer.writerow({"time": [labels[row]], "voltage": values[row]})

    append_to_file(logfile, f"[appended data] \tlen:labels/values: {len(labels)}/{len(values)}")

    if len(labels) > 14 or len(values) > 14:
        while len(labels) > 14:
            labels.pop(0)

        while len(values) > 14:
            values.pop(0)

        append_to_file(logfile, f"[shortened] \tlen:labels/values: {len(labels)}/{len(values)}")


def append_to_file(file, message):
    with open(file, "r+") as file:
        file.readlines()
        file.write("\n" + message)


ttn_client = mqtt.Client()
ttn_client.on_connect = on_connect
ttn_client.on_message = on_message
ttn_client.username_pw_set(APPID, PSW)
ttn_client.connect("eu.thethings.network", 1883, 60)  # MQTT port over TLS
ttn_client.loop_start()

# if __name__ == '__main__':
#     app.run(host='192.168.2.111', port=80, debug=True)
