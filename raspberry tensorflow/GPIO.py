import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(26,GPIO.OUT)

def Warn_sart():
   GPIO.output(26,GPIO.HIGH)
def Warn_stop():
   GPIO.output(26,GPIO.LOW)
   
   

  
