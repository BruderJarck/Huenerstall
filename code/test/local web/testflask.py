
from flask import Flask, render_template
import datetime
import paho.mqtt.client as mqtt
import json
import base64

APPEUI = '70B3D57ED001A086'
APPID = 'tempsens71263'
PSW = 'ttn-account-v2.6p1nkE0mLVt8YrtlAwJaWZixMQgHmc3jwdBd4ozDulw'

app = Flask(__name__)
payload = ["none received yet", "none received yet"]
j_msg = {"metadata": {"time": "none received yet"}}

@app.route("/")
def hello():
    now = datetime.datetime.now()
    time_string = now.strftime("%Y-%m-%d %H:%M")
    template_data = {
        'title': 'OpenHennery webinterface',
        'time_received': j_msg["metadata"]["time"],
        'door_state': str(payload[0]),
        'bat_voltage': str(int(payload[1])/10)
    }
    return render_template('index.html', **template_data)

def on_connect(client, userdata, flags, rc):
    client.subscribe('+/devices/+/up'.format(APPEUI))


def on_message(client, userdata, msg):
    global payload, j_msg
    j_msg = json.loads(msg.payload.decode('utf-8'))
    payload = base64.b64decode(j_msg['payload_raw'])

    print('---'*10)
    print(j_msg)
    [print(x) for x in payload]
    print('---'*10)

# set paho.mqtt callback
ttn_client = mqtt.Client()
ttn_client.on_connect = on_connect
ttn_client.on_message = on_message
ttn_client.username_pw_set(APPID, PSW)
ttn_client.connect("eu.thethings.network", 1883, 60)  # MQTT port over TLS

try:
    ttn_client.loop_start()
except KeyboardInterrupt:
    print('disconnect')
    ttn_client.disconnect()


