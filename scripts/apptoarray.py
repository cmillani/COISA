import os
import numpy

# files = ["ackermann.x", "array.x", "fib.x", "lists.x", "matrix.x", "sieve.x", "heapsort.x", "random.x"]
files = ["ackermann.x", "array.x", "fib.x", "matrix.x", "sieve.x", "heapsort.x", "random.x"]
# files = ["a.x"]
folder = "../benchmarks/bin/os/"
o = "s"
# for o in optimizations:
output = []
for f in files:
    array = []
    filename = folder + f
    file = open(filename, 'r')
    allfile = file.read()
    for c in allfile:
        output.append(ord(c))
    print "================================================================="
    print f
    print "================================================================="
    print output
    print len(output)
    output = []


        
        
