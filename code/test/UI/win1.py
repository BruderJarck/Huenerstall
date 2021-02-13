# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'win1.ui'
#
# Created by: PyQt5 UI code generator 5.15.2
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets
import paho.mqtt.client as mqtt
import json
import base64

APPEUI = '70B3D57ED001A086'
APPID = 'tempsens71263'
PSW = 'ttn-account-v2.6p1nkE0mLVt8YrtlAwJaWZixMQgHmc3jwdBd4ozDulw'

class Ui_MainWindow(object):
    def __init__(self):
        self.counter = 0

    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(804, 451)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.graphicsView = QtWidgets.QGraphicsView(self.centralwidget)
        self.graphicsView.setGeometry(QtCore.QRect(0, 0, 601, 411))
        self.graphicsView.setObjectName("graphicsView")

        self.widget = QtWidgets.QWidget(self.centralwidget)
        self.widget.setGeometry(QtCore.QRect(600, 0, 211, 161))
        self.widget.setObjectName("widget")

        self.verticalLayout = QtWidgets.QVBoxLayout(self.widget)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")

        self.label = QtWidgets.QLabel(self.widget)
        self.label.setObjectName("label")
        self.verticalLayout.addWidget(self.label)

        self.lcdNumber = QtWidgets.QLCDNumber(self.widget)
        self.lcdNumber.setObjectName("lcdNumber")
        self.verticalLayout.addWidget(self.lcdNumber)

        self.label_2 = QtWidgets.QLabel(self.widget)
        self.label_2.setObjectName("label_2")
        self.verticalLayout.addWidget(self.label_2)

        self.pushButton = QtWidgets.QPushButton(self.widget)
        self.pushButton.setObjectName("pushButton")
        self.verticalLayout.addWidget(self.pushButton)
        self.pushButton.clicked.connect(self.testbtn)

        MainWindow.setCentralWidget(self.centralwidget)

        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 804, 21))
        self.menubar.setObjectName("menubar")

        MainWindow.setMenuBar(self.menubar)

        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.label.setText(_translate("MainWindow", "Batterie spannung"))
        self.label_2.setText(_translate("MainWindow", "Türe ist: "))
        self.pushButton.setText(_translate("MainWindow", "PushButton"))

    def testbtn(self):
        self.counter += 10
        self.lcdNumber.display(str(self.counter))

def on_connect(client, userdata, flags, rc):

    client.subscribe('+/devices/+/up'.format(APPEUI))
    ui.label.setText("connected")
    print("connected")


def on_message(client, userdata, msg):

    j_msg = json.loads(msg.payload.decode('utf-8'))
    payload = base64.b64decode(j_msg['payload_raw'])

    # print(j_msg)
    a = [x for x in payload]
    ui.label.setText(f"{a}")
    print(a)





if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    # set paho.mqtt callback
    ttn_client = mqtt.Client()
    ttn_client.on_connect = on_connect
    ttn_client.on_message = on_message
    ttn_client.username_pw_set(APPID, PSW)
    ttn_client.connect("eu.thethings.network", 1883, 60)  # MQTT port over TLS
    ttn_client.loop_start()

    sys.exit(app.exec_())
