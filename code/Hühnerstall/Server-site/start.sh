#!/bin/bash
echo Starting Hühnerstall Server.
cd /home/pi/Huenerstall/venv/bin
. activate
cd /home/pi/Huenerstall/Hühnerstall/Server-site
gunicorn -w 2 -b 192.168.2.110:8083 hühnerstall-server:app
