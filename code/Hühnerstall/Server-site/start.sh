#!/bin/bash
echo Starting Flask example app.
cd /home/pi/Huenerstall/venv/bin
. activate
cd /home/pi/Huenerstall/code/test/'local web'
gunicorn -w 2 -b 192.168.2.110:8083 testflask_mqtt:app
