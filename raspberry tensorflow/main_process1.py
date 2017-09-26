#About ZERO Team finish deep learning
#please protection our reputation
#My name is Barry
import sys
import os
from multiprocessing import *

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import *
from  PyQt5.QtWidgets import *
from PyQt5.QtCore import *

import threading

import time
import picamera
import picamera.array
import cv2
import numpy as np

import ui_source
import model
import GPIO

  
import threading
import tensorflow as tf


class MainWindow(QMainWindow, ui_source.Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.img = cv2.imread("Tile.jpg")
        dest = cv2.cvtColor(self.img, cv2.COLOR_BGR2RGB)
        height, width, bpc = self.img.shape
        self.label_zero.setPixmap(QPixmap.fromImage(QImage(dest.data, width, height, QImage.Format_RGB888)))
        self.label_zero.setScaledContents(True)

        
        self.timer1 = QTimer()
        self.timer1.timeout.connect(self.update_image)
        self.timer1.stop()
        
        self.lcdNumber_time.display(time.strftime("%X",time.localtime()))
        self.timer = QBasicTimer() # 
        self.timer.start(1000, self) 
        
        self.resize(800, 600)
        self.setWindowTitle("ZERO TEAM")
        
        self.createMenu()

        self.pushButton_start.clicked.connect(self.pushButton_start_click)
        self.pushButton_save.clicked.connect(self.Start_preview)
        self.pushButton_reset.clicked.connect(self.Stop_preview)
        self.pushButton_saveimage.clicked.connect(self.Save_captual)

        #self.tableWidget_param = QTableWidget(5,4)
        #self.tableWidget_param.setItem(0,0,QTableWidgetItem("ZERO TEAM"))
        #self.formal = 1
        #self.Switch_all = 0
        #model.tf_model.init_model(self)
        model.tf_model.init_model(self)
        
    def timerEvent(self, event):
        if event.timerId() == self.timer.timerId():
            self.lcdNumber_time.display(time.strftime("%X",time.localtime()))
        else:
            super(WigglyWidget, self).timerEvent(event)   
        
    def QT_Widget(self,num, bianhao,cidian_result,cidian_type):
    
        self.tableWidget_param.setItem(num,0,QTableWidgetItem(str(bianhao)))
        if self.formal:
            self.tableWidget_param.setItem(num,1,QTableWidgetItem("Formal"))
        else:
            self.tableWidget_param.setItem(num,1,QTableWidgetItem("UnFormal"))
        self.tableWidget_param.setItem(num,2,QTableWidgetItem(str(cidian_result)))
        self.tableWidget_param.setItem(num,3,QTableWidgetItem(str(cidian_type)))
        
    def update_image(self):
##        with picamera.PiCamera() as camera:
##            #camera.resolution = (1024,768)
##            #camera.start_preview()
##            #time.sleep(2)
##            with picamera.array.PiRGBArray(camera) as stream:
##                camera.capture(stream,'rgb')
##                img = stream.array
##                T1 = time.time()
##                #human_string,score = q.get(True)
##                #self.QT_Widget(0,1,score,human_string)
        img = cv2.imread("51.jpg")        
        dest = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        height, width, bpc = self.img.shape
        self.label_show.setPixmap(QPixmap.fromImage(QImage(dest.data, width, height, QImage.Format_RGB888)))
        self.label_show.setScaledContents(True);
        
        print ("running")
    def pushButton_start_click(self):
        
        self.timer1.start(50)
        self.Switch_all = 1
        #q = Queue()
        #pm = Process(target = self.One_last(), args=(q,)) 
        #pm.setDaemon(True)   # 守护--就算主界面关闭，线程也会留守后台运行（不对!）
        #pm.start()
        #pm.join();

        
        
    def Start_preview(self):
        with picamera.PiCamera() as camera:
            #camera.resolution = (240,280)
            camera.start_preview()
            time.sleep(int(self.lineEdit_preview_time.text()))
        
        
    def Stop_preview(self):
        with picamera.PiCamera() as camera:
            camera.stop_preview()

    def Save_captual(self):
        with picamera.PiCamera() as camera:
            time.sleep(2)
            camera.capture(self.lineEdit_num.text()+".jpg")
      

    def createMenu(self):
        #menubar = QMenuBar(self)
        menubar = self.menuBar()
        menu = menubar.addMenu("param")
        menu.addAction(QAction("New", self, triggered=qApp.quit))

        menu.addSeparator()
        menu.addAction(QAction("Close", self, triggered=lambda :QMessageBox.about(self, 'Close','Closing')))
        
        menu = menubar.addMenu("counter")
        menu.addAction(QAction("Un", self, triggered=qApp.quit))
    def One_last(self):
        
        with tf.Session() as sess:  
            softmax_tensor = sess.graph.get_tensor_by_name('final_result:0')
            with picamera.PiCamera() as camera:
                camera.resolution = (1024,768)
                #camera.start_preview()
                #time.sleep(2)
                with picamera.array.PiRGBArray(camera) as stream:
                    while True:
                        camera.capture(stream,'rgb')
                        self.img = stream.array
                        image = tf.gfile.FastGFile("test.jpg", 'rb').read()
                        T1 = time.time()
                        predict = sess.run(softmax_tensor, {'DecodeJpeg/contents:0': image})
                        T2 = time.time()
                        top = predict[0].argsort()[-len(predict[0]):][::-1]  

                        human_string = self.labels[0]
                        score = str(predict[0][0])
                        q.put(human_string,score)
                        self.Spend_time = T2 - T1
                        print (self.Spend_time)
                        print (human_string,score)
    
    def main():
        app = QApplication(sys.argv)
        win = MainWindow()
        win.show()
        sys.exit(app.exec_());
        
if __name__ == '__main__':
    zero = MainWindow
    zero.main()


