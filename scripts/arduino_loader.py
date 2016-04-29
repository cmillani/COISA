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
elif len(sys.argv) >= 4 and sys.argv[2] == "-sim":
    zero = serial.Serial(sys.argv[3])
else:
    zero = serial.Serial("/dev/cu.usbmodem1411") # Upload using USB
time.sleep(2) # make sure the connection is ok

print len(executable)
print 'Waiting'
print '\nStarting'
# print (len(executable) & 0xFF)
# print ((len(executable) >> 8) & 0xFF)

zero.write(chr(82))
zero.write(chr(68))

sys.stdout.write(zero.read())
sys.stdout.write(zero.read())
sys.stdout.write(zero.read())
sys.stdout.write(zero.read())
sys.stdout.write(zero.read())

zero.write(chr(len(executable) & 0xFF))
zero.write(chr((len(executable) >> 8) & 0xFF))

print "Sending"
count = 0

for c in executable:
    zero.write(chr(ord(c)))
    time.sleep(0.02)
    
print "###########################################"
while True:
    
    received = zero.read()
    sys.stdout.write(received)
    # received = zero.read()
    
    # if (received == '\0'):
    #     break
zero.close()
print "End"