import serial
import sys
import time

import signal

# print sys.argv[1]
print "Starting"
file = open(sys.argv[1], 'rb')
executable = file.read()
# print len(executable)

# zero = serial.Serial("/dev/tty.Zero-DevB") # Upload using bluetooth
try:
	if len(sys.argv) >= 3 and sys.argv[2] == "-bt":
            zero = serial.Serial("/dev/cu.ZE002-DevB")
            # zero = serial.Serial("/dev/tty.CoisaBot-DevB") # Upload using bluetooth
            # zero = serial.Serial("/dev/cu.Zero2-DevB") # Upload using bluetooth
	    # zero = serial.Serial("/dev/tty.COLABOT2-DevB") # Upload using bluetooth
	elif len(sys.argv) >= 4 and sys.argv[2] == "-sim":
	    zero = serial.Serial(sys.argv[3])
	else:
        # zero = serial.Serial("/dev/cu.usbmodem1411") # Upload using USB
            # zero = serial.Serial("/dev/cu.usbmodem1421") # Upload using USB
            # zero = serial.Serial("/dev/cu.wchusbserial1420") # Upload using USB
            zero = serial.Serial("/dev/cu.wchusbserial1410") # Upload using USB
except Exception:
		print(Exception)
		print('Unable to connect')
		sys.exit(0)
	
def should_stop(signal, frame):
	print('\nExiting!')
	zero.close()
	sys.exit(0)
    
    
def send_package(package, expected):
    for i in range(5):
        print("\t*Try #"+str(i) + str(time.time()))

        zero.write(package)
        print ("BYTES IN BUFFER >>>>> " + str(zero.inWaiting()))
        resp = zero.read(20)
        print (">" + resp + "<" + str(time.time()))
        if (resp[0:5] == expected):
            break
        if (i == 4):
            print("Error sending package")
            sys.exit(0)
        else:
            print("Package Fail - Trying again!");
            zero.flushOutput()
            time.sleep(10)
            if (zero.inWaiting()/20 > 0):
                resp = zero.read(20)
                if (resp[0:5] == expected):
                    break
            print ("BYTES IN BUFFER >>>>> " + str(zero.inWaiting()))
            zero.flushInput()
def read_and_handle(expected):
    zero.read(20)
    if (resp[0:5] == expected):
        return 1
    elif (resp[0:5] == "TMOUT"):
        return 2
    else:
        return 0
    
signal.signal(signal.SIGINT, should_stop) # how to handle ctrl + c

time.sleep(2) # make sure the connection is ok

print 'Connected!'

print("*******SENDING FIRST COMMAND*******")
command = "RD"
for j in range(16):
    command += (chr(0))
command += (chr((len(executable) >> 8) & 0xFF))
command += (chr(len(executable) & 0xFF))

send_package(command, "OK-RD")

print "*******Sending*******"
count = 0
package_num = 0
while (count < len(executable)):
    string = "PK"+executable[count:min(count+18, len(executable))]
    while (len(string) < 20) :
        string += "\0" #To complete last package if needed
    count = count + min(18, len(executable) - count)

    print("*******SENDING PACKAGE #" + str(package_num) + "*******")
    send_package(string, "OK-PK")
    package_num += 1
    
print "###########################################"
while True:
    
    received = zero.read()
    sys.stdout.write(received)
    # received = zero.read()
    
    # if (received == '\0'):
    #     break
