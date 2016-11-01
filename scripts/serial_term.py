import serial
import sys
import time

# print sys.argv[1]
print "Starting"

if len(sys.argv) >= 2 and sys.argv[1] == "-bt":
    zero = serial.Serial("/dev/tty.COLABOT2-DevB") # Upload using bluetooth
else:
    zero = serial.Serial("/dev/cu.wchusbserial1410") # Upload using USB


while True:
    
    received = zero.read()
    sys.stdout.write(received)
    
zero.close()
print "End"
