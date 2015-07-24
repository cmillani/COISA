import os

optimizations = ["0","1","2","3","s"]
# optimizations = ["0"]
files = ["ackermann.x", "array.x", "fib.x", "lists.x", "matrix.x", "sieve.x", "heapsort.x", "random.x"]
# files = ["a.x"]
count = 1

for o in optimizations:
    for f in files:
        filename1 = "tests/" + f + ".stack.o" + o
        filename2 = "tests/" + f + ".size.o" + o
        file1 = open(filename1, 'r')
        file2 = open(filename2, 'r')
        for i in range(count):
            binary = int(file1.readline())
            stack = int(file2.readline())
            os.system("echo '" + str(stack + binary) + "' >> tests/" + f + ".memsum.o" + o)