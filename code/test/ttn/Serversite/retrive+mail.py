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
    print(payload[0], map(payload[1], 0, 255, 110, 140), )
    print('---'*10)

    subject = 'data retrieve test'
    content = [f"Hallo,\ndas hier ist eine der ersten Narichten die von meinen Hühnerstall-Prototy-Contollern automatisch, über lora geschickt wurden.\n "
               f"Jetzt muss das alles hier 'nur' noch eingebaut werden xD.\nIm Anhang ist noch eine Textdatei mit Informatioen zu der letzten Sendung, die wird immer standartmäßig dabei sein.\n\n"
               f"Türstatus: {payload[0]} (1=offen, 0=zu(wird noch in txt gändert, is aber schon spät))\n batvoltage: {map(payload[1], 0, 255, 1100, 1400)/100}V (das ist noch ein dummy wert)\n\nlg\n "
               f"Euer Maurice"]

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