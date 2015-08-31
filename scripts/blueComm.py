import serial
import sys
import time

print "Starting"

zero = serial.Serial("/dev/tty.Zero-DevB") # Upload using bluetooth
# zero = serial.Serial("/dev/cu.usbmodem1421") # Upload using USB
# time.sleep(2) # make sure the connection is ok



state = 0
while (1):
    value = input("0: Send new sequence (+ number of commands)\n1: Play Sequence\n2: Stop Sequence\n")
    zero.write(chr(value))
    

zero.close()