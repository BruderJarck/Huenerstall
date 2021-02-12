# Get and plot data from TTN Console using Python

import paho.mqtt.client as mqtt
import json
import base64

APPEUI = '70B3D57ED001A086'
APPID = 'tempsens71263'
PSW = 'ttn-account-v2.6p1nkE0mLVt8YrtlAwJaWZixMQgHmc3jwdBd4ozDulw'


def on_connect(client, userdata, flags, rc):

    client.subscribe('+/devices/+/up'.format(APPEUI))


def on_message(client, userdata, msg):

    j_msg = json.loads(msg.payload.decode('utf-8'))
    payload = base64.b64decode(j_msg['payload_raw'])

    print(j_msg)
    [print(x) for x in payload]


# set paho.mqtt callback
ttn_client = mqtt.Client()
ttn_client.on_connect = on_connect
ttn_client.on_message = on_message
ttn_client.username_pw_set(APPID, PSW)
ttn_client.connect("eu.thethings.network", 1883, 60)  # MQTT port over TLS
ttn_client.loop_forever()
