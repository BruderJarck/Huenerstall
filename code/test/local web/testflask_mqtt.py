import csv
from datetime import datetime
from flask import Flask, render_template
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

payload = [None, None, None, None, None, None, None, None]
j_msg = {"metadata": {"time": 100}}
labels = []
values = []
fieldnames = ["time", "voltage"]

logfile = "./log.txt"
datafile = "./data.csv"


@app.route('/')
@mobile_template('{mobile/}index.html')
def index(template):
    if payload[0] is not None:
        status_code = payload[0]
    else:
        status_code = "'unbekannter Statuscode'"
    if payload[1] == 0:
        doorstate = "geschlossen"
    elif payload[1] == 1:
        doorstate = "offen"
    else:
        doorstate = "'unbekannter Status'"

    if payload[2] == 0:
        zaunstate = "aus"
    elif payload[2] == 1:
        zaunstate = "an"
    else:
        zaunstate = "'unbekannter Status'"

    if payload[3] is not None:
        bat_voltage = str(int(payload[3]) / 10)
    else:
        bat_voltage = "'unbekannt'"

    if payload[4] is not None:
        uptime_h = payload[4]
    else:
        uptime_h = "'unbekannt'"

    if payload[5] is not None:
        uptime_m = payload[5]
    else:
        uptime_m = "'unbekannt'"

    if payload[6] is not None:
        downtime_h = payload[6]
    else:
        downtime_h = "'unbekannt'"

    if payload[7] is not None:
        downtime_m = payload[7]
    else:
        downtime_m = "'unbekannt'"

    template_data = {
        'title': 'OpenHennery webinterface',
        'status_code': status_code,
        'time_received': labels[-1],
        'door_state': doorstate,
        'zaun_state': zaunstate,
        'bat_voltage': bat_voltage,
        'labels': labels,
        'values': values,
        'uptime_h': uptime_h,
        'uptime_m': uptime_m,
        'downtime_h': downtime_h,
        'downtime_m': downtime_m
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

        append_to_file(logfile, f"[red data] \t\n{labels}\n{values}\nlen: {len(labels)}/{len(values)}")

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
    values += [int(payload[3]) / 10]

    append_to_file(logfile, f"[extended lists] \t{[f'{x}' for x in payload]}")

    with open("data.csv", "w") as file:
        file.truncate()

    with open("data.csv", "w") as file:
        writer = csv.DictWriter(file, fieldnames)
        writer.writeheader()
        for row in range(len(labels)):
            writer.writerow({"time": labels[row], "voltage": values[row]})

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
