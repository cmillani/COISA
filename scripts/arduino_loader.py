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
    zero = serial.Serial("/dev/tty.CoisaBot-DevB") # Upload using bluetooth
elif len(sys.argv) >= 4 and sys.argv[2] == "-sim":
    zero = serial.Serial(sys.argv[3])
else:
    zero = serial.Serial("/dev/cu.usbmodem1411") # Upload using USB
time.sleep(2) # make sure the connection is ok

print len(executable)
# print len(executable) & 0xFF
print 'Waiting'
print '\nStarting'
# print (len(executable) & 0xFF)
# print ((len(executable) >> 8) & 0xFF)

zero.write("R")# - R
zero.write("D")# - D
for i in range(16):
    zero.write(chr(0))
    
    
# zero.write(chr(0))
# zero.write(chr(1))
zero.write(chr((len(executable) >> 8) & 0xFF))
zero.write(chr(len(executable) & 0xFF))

# leng = zero.readline();
# print(leng)
resp = zero.read(20)
print (resp)
    
print "Sending"
count = 0

while (count < len(executable)):
    string = "PK"+executable[count:min(count+18, len(executable))]
    while (len(string) < 20) :
        string += "\0" #To complete last package if needed
    count = count + min(18, len(executable) - count)
    zero.write(string)
    
    resp = zero.read(20)
    print (resp)
    
print "###########################################"
while True:
    
    received = zero.read()
    sys.stdout.write(received)
    # received = zero.read()
    
    # if (received == '\0'):
    #     break
zero.close()
print "End"