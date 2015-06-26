import serial
import sys

print sys.argv[1]

file = open(sys.argv[1], 'rb')
executable = file.read()

zero = serial.Serial("/dev/tty.Zero-DevB")
print zero.name

zero.write(chr(len(executable)/4))

print "Will Read"

print zero.readline()

for c in executable:
    zero.write(chr(ord(c)))
    print hex(ord(c))
    # print unicode(zero.readline())
    
print "###########################################"
for i in range(0,len(executable)):
    received = zero.read()
    sys.stdout.write(hex(ord(received)))
    sys.stdout.write(' ')
    if ((i + 1) % 16 == 0):
        print
print
print "Pos vm_run:"
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
    print zero.readline()
    
print "End"