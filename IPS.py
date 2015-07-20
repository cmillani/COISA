import os

optimizations = ["0","1","2","3","s"]
# optimizations = ["0"]
files = ["ackermann.x", "array.x", "fib.x", "lists.x", "matrix.x", "sieve.x", "heapsort.x", "random.x"]
# files = ["a.x"]
folder = "OSX64Tests/"

for o in optimizations:
    for f in files:
        filename1 = folder + f + ".avrtime.o" + o
        IPS = 0.0
        filename2 = folder + f + ".count.o" + o
        file1 = open(filename1, 'r')
        file2 = open(filename2, 'r')
        time = float(file1.readline())
        count = float(file2.readline())
        result = ""
        if (time>0):
            result = str((count)/(time/1000000))
        else:
            result = "?"
        print result
        os.system("echo '" + (result) + "' > " + folder + f + ".IPS.o" + o)