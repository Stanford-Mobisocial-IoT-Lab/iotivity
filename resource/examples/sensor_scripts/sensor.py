import os
import time
from sys import argv
# Specify the path where you downloaded the pigpio DHT22.py module
#sys.path.append('/home/pi/my_programs')
os.chdir('/home/pi/my_programs')
os.system("sudo killall pigpiod")
os.system("sudo pigpiod")
import pigpio
# this connects to the pigpio daemon which must be started first
pi = pigpio.pi()

import DHT22
while True:
	s = DHT22.sensor(pi, 4)
	s.trigger()
	time.sleep(2)
	print('{:3.2f}'.format(s.humidity() / 1.))
	print('{:3.2f}'.format(s.temperature() / 1.))
	target = open("/home/pi/iotivity-1.1.0/out/linux/arm/release/resource/examples/data", 'w');
	target.truncate();
	#target.write(s.humidity() / 1.)
	#target.write(s.temperature() / 1.)
	target.write('{:3.2f}'.format(s.humidity() / 1.))
	target.write("\n")
	target.write('{:3.2f}'.format(s.temperature() / 1.))
	target.close()
	#time.sleep(2)
