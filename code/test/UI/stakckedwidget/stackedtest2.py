import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QShortcut, QWidget

from stackedtest import Ui_MainWindow

class MainWin:
    def __init__(self):
        self.main_win = QMainWindow()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self.main_win)

        self.ui.stackedWidget.setCurrentWidget(self.ui.page)

        self.ui.btenter.clicked.connect(self.enter)
        self.ui.back.clicked.connect(self.back)

        self.ui.InFirstname.textChanged.connect(self.changed)
        self.main_win.show()

    def enter(self):
        if self.ui.InLastname.text() != "" and self.ui.InFirstname.text() != "":
            self.ui.lOut.setText(f"hello {self.ui.InLastname.text()} {self.ui.InFirstname.text()}")
            self.ui.stackedWidget.setCurrentWidget(self.ui.page_2)
        else:
            self.ui.InFirstname.setText("fill all fields")

    def back(self):
        self.ui.InLastname.clear()
        self.ui.InFirstname.clear()
        self.ui.stackedWidget.setCurrentWidget(self.ui.page)

    def changed(self):
        if self.ui.InFirstname.text() == "hallo":
            self.ui.InLastname.setText("hallo")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    main_win = MainWin()
    sys.exit(app.exec_())