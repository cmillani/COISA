import serial
import sys
import time

# print sys.argv[1]
print "Starting"

zero = serial.Serial("/dev/cu.usbmodem1411") # Upload using USB

while True:
    
    received = zero.read()
    sys.stdout.write(received)
    
zero.close()
print "End"