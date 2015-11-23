import serial
import sys
import time

# print sys.argv[1]
print "Starting"
file = open(sys.argv[1], 'rb')
executable = file.read()
# print len(executable)

# zero = serial.Serial("/dev/tty.Zero-DevB") # Upload using bluetooth
if len(sys.argv) >= 3 and sys.argv[2] == "-bt":
    zero = serial.Serial("/dev/tty.Zero-DevB") # Upload using bluetooth
else:
    zero = serial.Serial("/dev/cu.usbmodem1411") # Upload using USB
time.sleep(2) # make sure the connection is ok

zero.write(chr(len(executable)/4 & 0xFF))
zero.write(chr((len(executable)/4 >> 8) & 0xFF))

print "Sending"
count = 0

for c in executable:
    zero.write(chr(ord(c)))
    
print "###########################################"
while True:
    
    received = zero.read()
    sys.stdout.write(received)
    # received = zero.read()
    
    if (received == '\0'):
        break
zero.close()
print "End"