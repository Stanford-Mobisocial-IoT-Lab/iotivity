from sys import argv
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(16, GPIO.IN)
while True:
  input_value = GPIO.input(16)
  if input_value == False:
    #print "The button has been pressed."
    target = open("/home/pi/iotivity-1.1.0/out/linux/arm/release/resource/examples/switch", 'w')
    target.truncate()
    target.write("1")
    target.close()
    while input_value == False:
      input_value = GPIO.input(16)
