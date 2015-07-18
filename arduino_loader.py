import serial
import sys
import time

print sys.argv[1]

file = open(sys.argv[1], 'rb')
executable = file.read()

# zero = serial.Serial("/dev/tty.Zero-DevB") # Upload using bluetooth
zero = serial.Serial("/dev/cu.usbmodem1421") # Upload using USB
print zero.name
time.sleep(5)

print len(executable)/4
print (len(executable)/4 & 0xFF)
print ((len(executable)/4 >> 8) & 0xFF)
zero.write(chr(len(executable)/4 & 0xFF))
zero.write(chr((len(executable)/4 >> 8) & 0xFF))

print "Will Read"

# a = ord(zero.read())
# zero.read()
# b = ord(zero.read())
# zero.read()
# zero.read()
# print (a | (b << 8))
#
# a = ord(zero.read())
# zero.read()
# b = ord(zero.read())
# zero.read()
# zero.read()
# print (a | (b << 8))
# print zero.readline()
# print zero.readline()

for c in executable:
    zero.write(chr(ord(c)))
    # print hex(ord(c))
    # print unicode(zero.readline())
    
print "###########################################"
# for i in range(0,len(executable)):
#     received = zero.read()
#     sys.stdout.write(hex(ord(received)))
#     sys.stdout.write(' ')
#     if ((i + 1) % 16 == 0):
#         print
# print
# print "Pos vm_run:"
while True:
    
    # sys.stdout.write(hex(ord(zero.read())))
#     sys.stdout.write(' ')
#     sys.stdout.write(hex(ord(zero.read())))
#     sys.stdout.write(' ')
#     sys.stdout.write(hex(ord(zero.read())))
#     sys.stdout.write(' ')
#     sys.stdout.write(hex(ord(zero.read())))
#     sys.stdout.write(' ')
#     sys.stdout.write(hex(ord(zero.read())))
#     print
    received = zero.read()
    sys.stdout.write(received)
    
print "End"