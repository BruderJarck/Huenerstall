import yagmail
from datetime import datetime
import paho.mqtt.client as mqtt
import json
import base64

APPEUI = '70B3D57ED001A086'
APPID = 'tempsens71263'
PSW = 'ttn-account-v2.6p1nkE0mLVt8YrtlAwJaWZixMQgHmc3jwdBd4ozDulw'

now = datetime.now()
airtime = 0

current_time = now.strftime("%H:%M:%S")
user = 'huestajarck@gmail.com'
app_password = 'xnjmzfzrspcvcevp'
to = ['huestajarck@gmail.com']#, 'diana.jarck@gmx.de', 'andreas.jarck@gmx.de']  # , 'ajaygaly@gmail.com', 'maurice.jarck@gmx.de']


def map(x, in_min, in_max, out_min, out_max):
    return int((x-in_min) * (out_max-out_min) / (in_max-in_min) + out_min)


def on_connect(client, userdata, flags, rc):
    client.subscribe('+/devices/+/up'.format(APPEUI))


def on_message(client, userdata, msg):
    j_msg = json.loads(msg.payload.decode('utf-8'))

    # global airtime
    # airtime += j_msg['airtime']
    payload = base64.b64decode(j_msg['payload_raw'])

    print('---'*10)
    print(j_msg)
    [print(x) for x in payload]
    print('---'*10)

    subject = 'data retrieve test'
    content = []
    for x in payload:
        content.append(f"\n {x}")

    with open("metadata.txt", "w") as txt:
        txt.write(json.dumps(j_msg, indent=4))

    with yagmail.SMTP(user, app_password) as yag:
        yag.send(to, subject, content, attachments="metadata.txt")
        print('Sent email successfully')

# set paho.mqtt callback
ttn_client = mqtt.Client()
ttn_client.on_connect = on_connect
ttn_client.on_message = on_message
ttn_client.username_pw_set(APPID, PSW)
ttn_client.connect("eu.thethings.network", 1883, 60)  # MQTT port over TLS

try:
    ttn_client.loop_forever()
except KeyboardInterrupt:
    print('disconnect')
    ttn_client.disconnect()