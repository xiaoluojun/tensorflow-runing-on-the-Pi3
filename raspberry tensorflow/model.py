import tensorflow as tf
import sys  
import picamera   
import threading 
import time

class tf_model():
    def init_model(self):  
        self.labels = []  
        for label in tf.gfile.GFile("output_labels.txt"):  
            self.labels.append(label.rstrip())  
           
        # 加载Graph  
        with tf.gfile.FastGFile("output_graph.pb", 'rb') as f:  
            graph_def = tf.GraphDef()  
            graph_def.ParseFromString(f.read())  
            tf.import_graph_def(graph_def, name='')
  
        '''
        for index in top:  
            human_string = labels[index]  
            score = predict[0][index]  
            print(human_string, score)
        '''
    def One_last(self):
        while True:
            with tf.Session() as sess:  
                softmax_tensor = sess.graph.get_tensor_by_name('final_result:0')
                
                image = tf.gfile.FastGFile("test.jpg", 'rb').read()
                T1 = time.time()
                predict = sess.run(softmax_tensor, {'DecodeJpeg/contents:0': image})
                T2 = time.time()
                top = predict[0].argsort()[-len(predict[0]):][::-1]
                
                print ("test start3")
                human_string = self.labels[0]
                score = predict[0][0]
                Spend_time = T2 - T1
                print ("test start1")
                print (Spend_time)
                print ("test start2")
                print (human_string,score)

        
        #return human_string,score
    def pass_human_string(self):
        return self.human_string
    def pass_score(self):
        return self.score
    
           


