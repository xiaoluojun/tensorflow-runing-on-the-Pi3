import tensorflow as tf
import sys  
import picamera
import picamera.array
import threading 
import time
from multiprocessing import *

labels = []

def init_mode():
     
    for label in tf.gfile.GFile("output_labels.txt"):  
        labels.append(label.rstrip())  
                   
    # 加载Graph  
    with tf.gfile.FastGFile("output_graph.pb", 'rb') as f:  
        graph_def = tf.GraphDef()  
        graph_def.ParseFromString(f.read())  
        tf.import_graph_def(graph_def, name='')     
def run_model():
    
    
    while True:
        T1 = time.time()
        with picamera.PiCamera() as camera:

            #camera.capture("test.jpg")
            with picamera.array.PiRGBArray(camera) as stream:        
                image = tf.gfile.FastGFile("test.jpg", 'rb').read()
                with tf.Session() as sess:  
                    softmax_tensor = sess.graph.get_tensor_by_name('final_result:0')  
                    predict = sess.run(softmax_tensor, {'DecodeJpeg/contents:0': image})  
                   
                    # 根据分类概率进行排序  
                    top = predict[0].argsort()[-len(predict[0]):][::-1]  
                T2 = time.time()
                Spend_time = T2 - T1
                print (Spend_time)             
                for index in top:  
                    human_string = labels[index]  
                    score = predict[0][index]  
                    print(human_string, score)
if __name__ == '__main__':
    init_mode()
    t = Process(target = run_model(), args=()) 
   # t.setDaemon(True)   # 守护--就算主界面关闭，线程也会留守后台运行（不对!）
    t.start()
    t.join()
    print ("Main function...");
           


