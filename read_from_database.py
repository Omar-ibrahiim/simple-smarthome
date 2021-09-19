from GUI import Ui_MainWindow
from firebase import firebase
import sys
from PyQt5 import QtWidgets, QtCore



class ApplicationWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super(ApplicationWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.firebase = firebase.FirebaseApplication('https://ourtask-db996.firebaseio.com', None)
        self.ui.timer = QtCore.QTimer(self)
        self.ui.timer.setInterval(200)  # in milliseconds
        self.ui.timer.start()
        self.ui.timer.timeout.connect(self.real_time_data)
        self.readings = []
        # self.ui.Start.clicked.connect(self.read_plot_from_db)
    def real_time_data(self):
        # after reading the data from the database and append it to the list we will get the len of the list and use it to generate a list1 that contain
        # number from 1 to len(list)

        self.readings.append(self.firebase.get('/Temperature_readings/Read data', None))
        time=list(range(len(self.readings)))
        self.read_plot_from_db(time,self.readings)


    def read_plot_from_db(self,x,y):
        self.ui.widget.clear()
        self.ui.widget.plot(x, y,symbol='o')
        self.ui.textEdit.setText(str(y[-1]))







def main():
    app = QtWidgets.QApplication(sys.argv)
    application = ApplicationWindow()
    application.show()
    app.exec_()


if __name__ == "__main__":
    main()
# ****************************************

# list = []
#
# firebase = firebase.FirebaseApplication('https://ourtask-db996.firebaseio.com',None)
#
# for i in range(0,10):
#     list.append(firebase.get('/Reading', None))
# print(list)
# *****************************************

