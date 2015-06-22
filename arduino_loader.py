import serial
import sys

print sys.argv[1]

file = open(sys.argv[1], 'rb')
executable = file.read()

zero = serial.Serial("/dev/tty.Zero-DevB")
print zero.name

zero.write(chr(len(executable)/4))

for c in executable:
    zero.write(chr(ord(c)))
    print chr(ord(c))
    # print unicode(zero.readline())