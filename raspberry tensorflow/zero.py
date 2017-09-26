#About ZERO Team finish deep learning
#please protection our reputation
#My name is Barry
import sys
import os
import queue
from multiprocessing import *

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import *
from  PyQt5.QtWidgets import *
from PyQt5.QtCore import *

import threading

import time
#import picamera
#import cv2
import numpy as np
import tensorflow as tf

import ui_source
#import model
#import GPIO

  
import threading


class MainWindow(QMainWindow, ui_source.Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        #self.img = cv2.imread("Tile.jpg")
        #dest = cv2.cvtColor(self.img, cv2.COLOR_BGR2RGB)
        #height, width, bpc = self.img.shape
        #self.label_zero.setPixmap(QPixmap.fromImage(QImage(dest.data, width, height, QImage.Format_RGB888)))
        #self.label_zero.setScaledContents(True)

        
        self.timer1 = QTimer()
        #self.timer1.timeout.connect(self.update_image)
        self.timer1.stop()
        
        self.lcdNumber_time.display(time.strftime("%X",time.localtime()))
        self.timer = QBasicTimer() # QTimer()貌似不行，不知何故？
        self.timer.start(1000, self) 
        
        self.resize(800, 600)
        self.setWindowTitle("ZERO TEAM")
        
        self.createMenu()

        self.pushButton_start.clicked.connect(self.pushButton_start_click)
        #self.pushButton_save.clicked.connect(self.Start_preview)
        #self.pushButton_reset.clicked.connect(self.Stop_preview)
        #self.pushButton_saveimage.clicked.connect(self.Save_captual)

        #self.tableWidget_param = QTableWidget(5,4)
        #self.tableWidget_param.setItem(0,0,QTableWidgetItem("ZERO TEAM"))
        self.formal = 1
        self.Num_val = 0
        #self.Switch_all = 0
        #model.tf_model.init_model(self)
        #model.tf_model.init_model(self)
        
    def timerEvent(self, event):
        if event.timerId() == self.timer.timerId():
            self.lcdNumber_time.display(time.strftime("%X",time.localtime()))
        else:
            super(WigglyWidget, self).timerEvent(event)   
        
    def QT_Widget(self,num, bianhao,cidian_result,cidian_type):
    
        self.tableWidget_param.setItem(num,0,QTableWidgetItem(str(bianhao)))
        if self.formal:
            self.tableWidget_param.setItem(num,1,QTableWidgetItem("Runing"))
        else:
            self.tableWidget_param.setItem(num,1,QTableWidgetItem("Stop"))
        self.tableWidget_param.setItem(num,2,QTableWidgetItem(str(cidian_result)))
        self.tableWidget_param.setItem(num,3,QTableWidgetItem(str(cidian_type)))
    def update_result(self):
        self.label_show_time.setText(Time.get())
        if self.Num_val == 6:
            self.Num_val=0
        self.QT_Widget(self.Num_val, 2,Val.get(),Type.get())
        self.Num_val = self.Num_val+1
    #def update_image(self):
       # T1 = time.time()
        #self.img = cv2.imread("test.jpg")        
        #dest = cv2.cvtColor(self.img, cv2.COLOR_BGR2RGB)
        #height, width, bpc = self.img.shape
        #self.label_show.setPixmap(QPixmap.fromImage(QImage(dest.data, width, height, QImage.Format_RGB888)))
        #self.label_show.setScaledContents(True);
        #T2 = time.time()
        #self.Spend_time = T2 - T1
        #print (self.Spend_time)
        
    def pushButton_start_click(self):
        
        workthread.start()
        workthread._signal.connect(self.update_result)
        camerathread.start()
        #camerathread.camer.connect(self.update_image)
        
        #self.timer1.start(1)

    def createMenu(self):
        #menubar = QMenuBar(self)
        menubar = self.menuBar()
        menu = menubar.addMenu("param")
        menu.addAction(QAction("New", self, triggered=qApp.quit))

        menu.addSeparator()
        menu.addAction(QAction("Close", self, triggered=lambda :QMessageBox.about(self, 'Close','Closing')))
        
        menu = menubar.addMenu("counter")
        menu.addAction(QAction("Un", self, triggered=qApp.quit))
   
    
    def main():
        app = QApplication(sys.argv)
        win = MainWindow()
        win.show()
        app.exec_();
class ModelThread(QThread):
    _signal = pyqtSignal()
    def __init__(self):
        super(ModelThread,self).__init__()
    def run(self):
        labels = []
        for label in tf.gfile.GFile("output_labels.txt"):  
            labels.append(label.rstrip())  
           
        # 加载Graph  
        with tf.gfile.FastGFile("output_graph.pb", 'rb') as f:  
            graph_def = tf.GraphDef()  
            graph_def.ParseFromString(f.read())  
            tf.import_graph_def(graph_def, name='')
        while True:
            T1 = time.time()
            image = tf.gfile.FastGFile("test.jpg", 'rb').read()
            with tf.Session() as sess:  
                softmax_tensor = sess.graph.get_tensor_by_name('final_result:0')
                predict = sess.run(softmax_tensor, {'DecodeJpeg/contents:0': image})
            T2 = time.time()
            top = predict[0].argsort()[-len(predict[0]):][::-1]  

            human_string = str(labels[0])
            score = str(predict[0][0])
            
            Spend_time =str( T2 - T1)
            date = [Spend_time,human_string,score]
            Time.put(Spend_time)
            Type.put(human_string)
            Val.put(score)
            self._signal.emit()
			
class CameraThread(QThread):
    camer = pyqtSignal()
    def __init__(self):
        super(CameraThread,self).__init__()
    def run(self):
        print  ("cameratherading>>>....")
       

if __name__ == '__main__':
    Time = queue.Queue()
    Type = queue.Queue()
    Val = queue.Queue()
    result = {}
    zero = MainWindow
    workthread = ModelThread()
    camerathread = CameraThread()
    zero.main()


