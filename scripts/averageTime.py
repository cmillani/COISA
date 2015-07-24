import os
import numpy

optimizations = ["0","1","2","3","s"]
# optimizations = ["0"]
files = ["ackermann.x", "array.x", "fib.x", "lists.x", "matrix.x", "sieve.x", "heapsort.x", "random.x"]
# files = ["ackermann.x", "array.x", "fib.x", "matrix.x", "sieve.x", "heapsort.x", "random.x"]
# files = ["a.x"]
folder = "../tests/"
o = "s"
# for o in optimizations:
for f in files:
    array = []
    filename = folder + f + ".time.o" + o
    file = open(filename, 'r')
    count = .0
    totsum = .0
    lines = file.readlines()
    for line in lines:
        count += 1
        array.append(float(line))
        totsum += float(line)
    result = (totsum/count)
    print array
    var = numpy.var(array)
    std = numpy.std(array)
    print var
    # print filename + str((totsum/count))
    os.system("echo '" + str(result) + "' > " + folder + f + ".avrtime.o" + o)
    os.system("echo '" + str(var) + "' > " + folder + f + ".var.o" + o)
    os.system("echo '" + str(std) + "' > " + folder + f + ".std.o" + o)
        
        
