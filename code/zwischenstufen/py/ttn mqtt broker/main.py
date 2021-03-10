# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'MainWindow.ui'
#
# Created by: PyQt5 UI code generator 5.15.2
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(339, 506)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName("gridLayout")
        self.tabWidget = QtWidgets.QTabWidget(self.centralwidget)
        self.tabWidget.setStyleSheet("QTabBar::tab { height: 30px;  }")
        self.tabWidget.setIconSize(QtCore.QSize(23, 22))
        self.tabWidget.setMovable(True)
        self.tabWidget.setObjectName("tabWidget")
        self.conections = QtWidgets.QWidget()
        self.conections.setObjectName("conections")
        self.verticalLayout_5 = QtWidgets.QVBoxLayout(self.conections)
        self.verticalLayout_5.setObjectName("verticalLayout_5")
        self.stackedWidgetConnections = QtWidgets.QStackedWidget(self.conections)
        self.stackedWidgetConnections.setEnabled(True)
        self.stackedWidgetConnections.setAutoFillBackground(False)
        self.stackedWidgetConnections.setObjectName("stackedWidgetConnections")
        self.viewConn = QtWidgets.QWidget()
        self.viewConn.setObjectName("viewConn")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.viewConn)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.connectionTable = QtWidgets.QTableView(self.viewConn)
        self.connectionTable.setDragDropMode(QtWidgets.QAbstractItemView.NoDragDrop)
        self.connectionTable.setDefaultDropAction(QtCore.Qt.TargetMoveAction)
        self.connectionTable.setAlternatingRowColors(False)
        self.connectionTable.setSelectionMode(QtWidgets.QAbstractItemView.SingleSelection)
        self.connectionTable.setSortingEnabled(True)
        self.connectionTable.setObjectName("connectionTable")
        self.verticalLayout_3.addWidget(self.connectionTable)
        self.btAddConnection_3 = QtWidgets.QPushButton(self.viewConn)
        self.btAddConnection_3.setObjectName("btAddConnection_3")
        self.verticalLayout_3.addWidget(self.btAddConnection_3)
        self.btAddConnection = QtWidgets.QPushButton(self.viewConn)
        self.btAddConnection.setObjectName("btAddConnection")
        self.verticalLayout_3.addWidget(self.btAddConnection)
        self.stackedWidgetConnections.addWidget(self.viewConn)
        self.addConn = QtWidgets.QWidget()
        self.addConn.setObjectName("addConn")
        self.verticalLayout_6 = QtWidgets.QVBoxLayout(self.addConn)
        self.verticalLayout_6.setObjectName("verticalLayout_6")
        self.label_2 = QtWidgets.QLabel(self.addConn)
        self.label_2.setObjectName("label_2")
        self.verticalLayout_6.addWidget(self.label_2)
        self.lineEdit = QtWidgets.QLineEdit(self.addConn)
        self.lineEdit.setObjectName("lineEdit")
        self.verticalLayout_6.addWidget(self.lineEdit)
        self.label = QtWidgets.QLabel(self.addConn)
        self.label.setObjectName("label")
        self.verticalLayout_6.addWidget(self.label)
        self.lineEdit_3 = QtWidgets.QLineEdit(self.addConn)
        self.lineEdit_3.setObjectName("lineEdit_3")
        self.verticalLayout_6.addWidget(self.lineEdit_3)
        self.label_3 = QtWidgets.QLabel(self.addConn)
        self.label_3.setObjectName("label_3")
        self.verticalLayout_6.addWidget(self.label_3)
        self.lineEdit_2 = QtWidgets.QLineEdit(self.addConn)
        self.lineEdit_2.setObjectName("lineEdit_2")
        self.verticalLayout_6.addWidget(self.lineEdit_2)
        self.label_6 = QtWidgets.QLabel(self.addConn)
        self.label_6.setObjectName("label_6")
        self.verticalLayout_6.addWidget(self.label_6)
        self.lineEdit_4 = QtWidgets.QLineEdit(self.addConn)
        self.lineEdit_4.setObjectName("lineEdit_4")
        self.verticalLayout_6.addWidget(self.lineEdit_4)
        self.label_4 = QtWidgets.QLabel(self.addConn)
        self.label_4.setObjectName("label_4")
        self.verticalLayout_6.addWidget(self.label_4)
        self.lineEdit_5 = QtWidgets.QLineEdit(self.addConn)
        self.lineEdit_5.setObjectName("lineEdit_5")
        self.verticalLayout_6.addWidget(self.lineEdit_5)
        self.label_5 = QtWidgets.QLabel(self.addConn)
        self.label_5.setObjectName("label_5")
        self.verticalLayout_6.addWidget(self.label_5)
        self.lineEdit_8 = QtWidgets.QLineEdit(self.addConn)
        self.lineEdit_8.setObjectName("lineEdit_8")
        self.verticalLayout_6.addWidget(self.lineEdit_8)
        self.label_8 = QtWidgets.QLabel(self.addConn)
        self.label_8.setObjectName("label_8")
        self.verticalLayout_6.addWidget(self.label_8)
        self.lineEdit_6 = QtWidgets.QLineEdit(self.addConn)
        self.lineEdit_6.setObjectName("lineEdit_6")
        self.verticalLayout_6.addWidget(self.lineEdit_6)
        self.pushButton_4 = QtWidgets.QPushButton(self.addConn)
        self.pushButton_4.setObjectName("pushButton_4")
        self.verticalLayout_6.addWidget(self.pushButton_4)
        self.pushButton_5 = QtWidgets.QPushButton(self.addConn)
        self.pushButton_5.setObjectName("pushButton_5")
        self.verticalLayout_6.addWidget(self.pushButton_5)
        self.pushButton_6 = QtWidgets.QPushButton(self.addConn)
        self.pushButton_6.setObjectName("pushButton_6")
        self.verticalLayout_6.addWidget(self.pushButton_6)
        self.stackedWidgetConnections.addWidget(self.addConn)
        self.viewDetailedConn = QtWidgets.QWidget()
        self.viewDetailedConn.setObjectName("viewDetailedConn")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.viewDetailedConn)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.label_11 = QtWidgets.QLabel(self.viewDetailedConn)
        self.label_11.setObjectName("label_11")
        self.verticalLayout_2.addWidget(self.label_11)
        self.lineEdit_12 = QtWidgets.QLineEdit(self.viewDetailedConn)
        self.lineEdit_12.setObjectName("lineEdit_12")
        self.verticalLayout_2.addWidget(self.lineEdit_12)
        self.label_13 = QtWidgets.QLabel(self.viewDetailedConn)
        self.label_13.setObjectName("label_13")
        self.verticalLayout_2.addWidget(self.label_13)
        self.lineEdit_17 = QtWidgets.QLineEdit(self.viewDetailedConn)
        self.lineEdit_17.setObjectName("lineEdit_17")
        self.verticalLayout_2.addWidget(self.lineEdit_17)
        self.label_7 = QtWidgets.QLabel(self.viewDetailedConn)
        self.label_7.setObjectName("label_7")
        self.verticalLayout_2.addWidget(self.label_7)
        self.lineEdit_15 = QtWidgets.QLineEdit(self.viewDetailedConn)
        self.lineEdit_15.setObjectName("lineEdit_15")
        self.verticalLayout_2.addWidget(self.lineEdit_15)
        self.label_12 = QtWidgets.QLabel(self.viewDetailedConn)
        self.label_12.setObjectName("label_12")
        self.verticalLayout_2.addWidget(self.label_12)
        self.lineEdit_14 = QtWidgets.QLineEdit(self.viewDetailedConn)
        self.lineEdit_14.setObjectName("lineEdit_14")
        self.verticalLayout_2.addWidget(self.lineEdit_14)
        self.label_9 = QtWidgets.QLabel(self.viewDetailedConn)
        self.label_9.setObjectName("label_9")
        self.verticalLayout_2.addWidget(self.label_9)
        self.lineEdit_18 = QtWidgets.QLineEdit(self.viewDetailedConn)
        self.lineEdit_18.setObjectName("lineEdit_18")
        self.verticalLayout_2.addWidget(self.lineEdit_18)
        self.label_14 = QtWidgets.QLabel(self.viewDetailedConn)
        self.label_14.setObjectName("label_14")
        self.verticalLayout_2.addWidget(self.label_14)
        self.lineEdit_16 = QtWidgets.QLineEdit(self.viewDetailedConn)
        self.lineEdit_16.setObjectName("lineEdit_16")
        self.verticalLayout_2.addWidget(self.lineEdit_16)
        self.label_10 = QtWidgets.QLabel(self.viewDetailedConn)
        self.label_10.setObjectName("label_10")
        self.verticalLayout_2.addWidget(self.label_10)
        self.lineEdit_13 = QtWidgets.QLineEdit(self.viewDetailedConn)
        self.lineEdit_13.setObjectName("lineEdit_13")
        self.verticalLayout_2.addWidget(self.lineEdit_13)
        self.pushButton_18 = QtWidgets.QPushButton(self.viewDetailedConn)
        self.pushButton_18.setObjectName("pushButton_18")
        self.verticalLayout_2.addWidget(self.pushButton_18)
        self.pushButton_7 = QtWidgets.QPushButton(self.viewDetailedConn)
        self.pushButton_7.setObjectName("pushButton_7")
        self.verticalLayout_2.addWidget(self.pushButton_7)
        self.pushButton_8 = QtWidgets.QPushButton(self.viewDetailedConn)
        self.pushButton_8.setObjectName("pushButton_8")
        self.verticalLayout_2.addWidget(self.pushButton_8)
        self.stackedWidgetConnections.addWidget(self.viewDetailedConn)
        self.verticalLayout_5.addWidget(self.stackedWidgetConnections)
        self.tabWidget.addTab(self.conections, "")
        self.dashboard = QtWidgets.QWidget()
        self.dashboard.setObjectName("dashboard")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.dashboard)
        self.verticalLayout.setObjectName("verticalLayout")
        self.stackedWidgetDashboard = QtWidgets.QStackedWidget(self.dashboard)
        self.stackedWidgetDashboard.setObjectName("stackedWidgetDashboard")
        self.viewDashbaord = QtWidgets.QWidget()
        self.viewDashbaord.setObjectName("viewDashbaord")
        self.verticalLayout_8 = QtWidgets.QVBoxLayout(self.viewDashbaord)
        self.verticalLayout_8.setObjectName("verticalLayout_8")
        self.widget = QtWidgets.QWidget(self.viewDashbaord)
        self.widget.setObjectName("widget")
        self.verticalLayout_8.addWidget(self.widget)
        self.btAddWidget = QtWidgets.QPushButton(self.viewDashbaord)
        self.btAddWidget.setObjectName("btAddWidget")
        self.verticalLayout_8.addWidget(self.btAddWidget)
        self.pushButton = QtWidgets.QPushButton(self.viewDashbaord)
        self.pushButton.setObjectName("pushButton")
        self.verticalLayout_8.addWidget(self.pushButton)
        self.stackedWidgetDashboard.addWidget(self.viewDashbaord)
        self.addWidget = QtWidgets.QWidget()
        self.addWidget.setObjectName("addWidget")
        self.verticalLayout_9 = QtWidgets.QVBoxLayout(self.addWidget)
        self.verticalLayout_9.setObjectName("verticalLayout_9")
        self.listWidget = QtWidgets.QListWidget(self.addWidget)
        self.listWidget.setObjectName("listWidget")
        self.verticalLayout_9.addWidget(self.listWidget)
        self.pushButton_11 = QtWidgets.QPushButton(self.addWidget)
        self.pushButton_11.setObjectName("pushButton_11")
        self.verticalLayout_9.addWidget(self.pushButton_11)
        self.pushButton_10 = QtWidgets.QPushButton(self.addWidget)
        self.pushButton_10.setObjectName("pushButton_10")
        self.verticalLayout_9.addWidget(self.pushButton_10)
        self.pushButton_9 = QtWidgets.QPushButton(self.addWidget)
        self.pushButton_9.setObjectName("pushButton_9")
        self.verticalLayout_9.addWidget(self.pushButton_9)
        self.stackedWidgetDashboard.addWidget(self.addWidget)
        self.verticalLayout.addWidget(self.stackedWidgetDashboard)
        self.tabWidget.addTab(self.dashboard, "")
        self.datalog = QtWidgets.QWidget()
        self.datalog.setObjectName("datalog")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout(self.datalog)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.stackedWidgetDatalog = QtWidgets.QStackedWidget(self.datalog)
        self.stackedWidgetDatalog.setObjectName("stackedWidgetDatalog")
        self.viewDatalog = QtWidgets.QWidget()
        self.viewDatalog.setObjectName("viewDatalog")
        self.verticalLayout_10 = QtWidgets.QVBoxLayout(self.viewDatalog)
        self.verticalLayout_10.setObjectName("verticalLayout_10")
        self.listView = QtWidgets.QListView(self.viewDatalog)
        self.listView.setObjectName("listView")
        self.verticalLayout_10.addWidget(self.listView)
        self.pushButton_2 = QtWidgets.QPushButton(self.viewDatalog)
        self.pushButton_2.setObjectName("pushButton_2")
        self.verticalLayout_10.addWidget(self.pushButton_2)
        self.pushButton_3 = QtWidgets.QPushButton(self.viewDatalog)
        self.pushButton_3.setObjectName("pushButton_3")
        self.verticalLayout_10.addWidget(self.pushButton_3)
        self.stackedWidgetDatalog.addWidget(self.viewDatalog)
        self.addDatalog = QtWidgets.QWidget()
        self.addDatalog.setObjectName("addDatalog")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.addDatalog)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.label_15 = QtWidgets.QLabel(self.addDatalog)
        self.label_15.setObjectName("label_15")
        self.gridLayout_2.addWidget(self.label_15, 0, 0, 1, 2)
        self.label_16 = QtWidgets.QLabel(self.addDatalog)
        self.label_16.setObjectName("label_16")
        self.gridLayout_2.addWidget(self.label_16, 1, 0, 1, 1)
        self.label_18 = QtWidgets.QLabel(self.addDatalog)
        self.label_18.setObjectName("label_18")
        self.gridLayout_2.addWidget(self.label_18, 3, 0, 1, 1)
        self.label_17 = QtWidgets.QLabel(self.addDatalog)
        self.label_17.setObjectName("label_17")
        self.gridLayout_2.addWidget(self.label_17, 4, 0, 1, 1)
        spacerItem = QtWidgets.QSpacerItem(251, 219, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.gridLayout_2.addItem(spacerItem, 6, 0, 1, 4)
        self.checkBox = QtWidgets.QCheckBox(self.addDatalog)
        self.checkBox.setObjectName("checkBox")
        self.gridLayout_2.addWidget(self.checkBox, 1, 3, 1, 1)
        self.checkBox_2 = QtWidgets.QCheckBox(self.addDatalog)
        self.checkBox_2.setObjectName("checkBox_2")
        self.gridLayout_2.addWidget(self.checkBox_2, 3, 3, 1, 1)
        self.lineEdit_7 = QtWidgets.QLineEdit(self.addDatalog)
        self.lineEdit_7.setObjectName("lineEdit_7")
        self.gridLayout_2.addWidget(self.lineEdit_7, 5, 0, 1, 5)
        self.pushButton_13 = QtWidgets.QPushButton(self.addDatalog)
        self.pushButton_13.setObjectName("pushButton_13")
        self.gridLayout_2.addWidget(self.pushButton_13, 7, 0, 1, 5)
        self.pushButton_12 = QtWidgets.QPushButton(self.addDatalog)
        self.pushButton_12.setObjectName("pushButton_12")
        self.gridLayout_2.addWidget(self.pushButton_12, 8, 0, 1, 4)
        self.comboBox = QtWidgets.QComboBox(self.addDatalog)
        self.comboBox.setObjectName("comboBox")
        self.gridLayout_2.addWidget(self.comboBox, 0, 3, 1, 1)
        self.stackedWidgetDatalog.addWidget(self.addDatalog)
        self.verticalLayout_4.addWidget(self.stackedWidgetDatalog)
        self.tabWidget.addTab(self.datalog, "")
        self.notification = QtWidgets.QWidget()
        self.notification.setObjectName("notification")
        self.verticalLayout_12 = QtWidgets.QVBoxLayout(self.notification)
        self.verticalLayout_12.setObjectName("verticalLayout_12")
        self.stackedWidgetNotifications = QtWidgets.QStackedWidget(self.notification)
        self.stackedWidgetNotifications.setObjectName("stackedWidgetNotifications")
        self.viewNotifi = QtWidgets.QWidget()
        self.viewNotifi.setObjectName("viewNotifi")
        self.verticalLayout_13 = QtWidgets.QVBoxLayout(self.viewNotifi)
        self.verticalLayout_13.setObjectName("verticalLayout_13")
        self.listView_2 = QtWidgets.QListView(self.viewNotifi)
        self.listView_2.setObjectName("listView_2")
        self.verticalLayout_13.addWidget(self.listView_2)
        self.pushButton_15 = QtWidgets.QPushButton(self.viewNotifi)
        self.pushButton_15.setObjectName("pushButton_15")
        self.verticalLayout_13.addWidget(self.pushButton_15)
        self.pushButton_14 = QtWidgets.QPushButton(self.viewNotifi)
        self.pushButton_14.setObjectName("pushButton_14")
        self.verticalLayout_13.addWidget(self.pushButton_14)
        self.stackedWidgetNotifications.addWidget(self.viewNotifi)
        self.addNotifi = QtWidgets.QWidget()
        self.addNotifi.setObjectName("addNotifi")
        self.verticalLayout_14 = QtWidgets.QVBoxLayout(self.addNotifi)
        self.verticalLayout_14.setObjectName("verticalLayout_14")
        self.label_19 = QtWidgets.QLabel(self.addNotifi)
        self.label_19.setObjectName("label_19")
        self.verticalLayout_14.addWidget(self.label_19)
        self.comboBox_2 = QtWidgets.QComboBox(self.addNotifi)
        self.comboBox_2.setObjectName("comboBox_2")
        self.verticalLayout_14.addWidget(self.comboBox_2)
        self.label_22 = QtWidgets.QLabel(self.addNotifi)
        self.label_22.setObjectName("label_22")
        self.verticalLayout_14.addWidget(self.label_22)
        self.lineEdit_9 = QtWidgets.QLineEdit(self.addNotifi)
        self.lineEdit_9.setObjectName("lineEdit_9")
        self.verticalLayout_14.addWidget(self.lineEdit_9)
        self.label_21 = QtWidgets.QLabel(self.addNotifi)
        self.label_21.setObjectName("label_21")
        self.verticalLayout_14.addWidget(self.label_21)
        self.lineEdit_10 = QtWidgets.QLineEdit(self.addNotifi)
        self.lineEdit_10.setObjectName("lineEdit_10")
        self.verticalLayout_14.addWidget(self.lineEdit_10)
        self.label_20 = QtWidgets.QLabel(self.addNotifi)
        self.label_20.setObjectName("label_20")
        self.verticalLayout_14.addWidget(self.label_20)
        self.lineEdit_11 = QtWidgets.QLineEdit(self.addNotifi)
        self.lineEdit_11.setObjectName("lineEdit_11")
        self.verticalLayout_14.addWidget(self.lineEdit_11)
        spacerItem1 = QtWidgets.QSpacerItem(17, 156, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout_14.addItem(spacerItem1)
        self.pushButton_16 = QtWidgets.QPushButton(self.addNotifi)
        self.pushButton_16.setObjectName("pushButton_16")
        self.verticalLayout_14.addWidget(self.pushButton_16)
        self.pushButton_17 = QtWidgets.QPushButton(self.addNotifi)
        self.pushButton_17.setObjectName("pushButton_17")
        self.verticalLayout_14.addWidget(self.pushButton_17)
        self.stackedWidgetNotifications.addWidget(self.addNotifi)
        self.verticalLayout_12.addWidget(self.stackedWidgetNotifications)
        self.tabWidget.addTab(self.notification, "")
        self.gridLayout.addWidget(self.tabWidget, 0, 0, 1, 1)
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        self.tabWidget.setCurrentIndex(0)
        self.stackedWidgetConnections.setCurrentIndex(0)
        self.stackedWidgetDashboard.setCurrentIndex(0)
        self.stackedWidgetDatalog.setCurrentIndex(0)
        self.stackedWidgetNotifications.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.btAddConnection_3.setText(_translate("MainWindow", "edit"))
        self.btAddConnection.setText(_translate("MainWindow", "add connection"))
        self.label_2.setText(_translate("MainWindow", "Connection Name"))
        self.label.setText(_translate("MainWindow", "TTN appEui"))
        self.label_3.setText(_translate("MainWindow", "TTN appId"))
        self.label_6.setText(_translate("MainWindow", "TTN accessKey"))
        self.label_4.setText(_translate("MainWindow", "Hostname / IP"))
        self.label_5.setText(_translate("MainWindow", "port"))
        self.label_8.setText(_translate("MainWindow", "keep alive [sec]"))
        self.pushButton_4.setText(_translate("MainWindow", "add"))
        self.pushButton_5.setText(_translate("MainWindow", "help"))
        self.pushButton_6.setText(_translate("MainWindow", "cancel"))
        self.label_11.setText(_translate("MainWindow", "Connection Name"))
        self.label_13.setText(_translate("MainWindow", "TTN appEui"))
        self.label_7.setText(_translate("MainWindow", "TTN appId"))
        self.label_12.setText(_translate("MainWindow", "TTN accessKey"))
        self.label_9.setText(_translate("MainWindow", "Hostname / IP"))
        self.label_14.setText(_translate("MainWindow", "port"))
        self.label_10.setText(_translate("MainWindow", "keep alive [sec]"))
        self.pushButton_18.setText(_translate("MainWindow", "apply"))
        self.pushButton_7.setText(_translate("MainWindow", "help"))
        self.pushButton_8.setText(_translate("MainWindow", "cancel"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.conections), _translate("MainWindow", "connections"))
        self.btAddWidget.setText(_translate("MainWindow", "add widget"))
        self.pushButton.setText(_translate("MainWindow", "del widget"))
        self.pushButton_11.setText(_translate("MainWindow", "add "))
        self.pushButton_10.setText(_translate("MainWindow", "help"))
        self.pushButton_9.setText(_translate("MainWindow", "cancel"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.dashboard), _translate("MainWindow", "dashboard"))
        self.pushButton_2.setText(_translate("MainWindow", "add datalog"))
        self.pushButton_3.setText(_translate("MainWindow", "del datalog"))
        self.label_15.setText(_translate("MainWindow", "selcet conncetion"))
        self.label_16.setText(_translate("MainWindow", "datalog"))
        self.label_18.setText(_translate("MainWindow", "csv excel style"))
        self.label_17.setText(_translate("MainWindow", "file location"))
        self.checkBox.setText(_translate("MainWindow", "datalog"))
        self.checkBox_2.setText(_translate("MainWindow", "excel csv syle"))
        self.pushButton_13.setText(_translate("MainWindow", "add"))
        self.pushButton_12.setText(_translate("MainWindow", "cancel"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.datalog), _translate("MainWindow", "datalog"))
        self.pushButton_15.setText(_translate("MainWindow", "add notification"))
        self.pushButton_14.setText(_translate("MainWindow", "del notification"))
        self.label_19.setText(_translate("MainWindow", "select conncetion"))
        self.label_22.setText(_translate("MainWindow", "host adress"))
        self.label_21.setText(_translate("MainWindow", "host password"))
        self.label_20.setText(_translate("MainWindow", "client adresses"))
        self.pushButton_16.setText(_translate("MainWindow", "add"))
        self.pushButton_17.setText(_translate("MainWindow", "cancel"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.notification), _translate("MainWindow", "notification"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())