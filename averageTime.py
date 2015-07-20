import os

optimizations = ["0","1","2","3","s"]
# optimizations = ["0"]
files = ["ackermann.x", "array.x", "fib.x", "lists.x", "matrix.x", "sieve.x", "heapsort.x", "random.x"]
# files = ["a.x"]
folder = "Linux64Tests/"

for o in optimizations:
    for f in files:
        filename = folder + f + ".time.o" + o
        file = open(filename, 'r')
        count = .0
        totsum = .0
        lines = file.readlines()
        for line in lines:
            count += 1
            totsum += float(line)
        result = (totsum/count)
        print filename + str((totsum/count))
        os.system("echo '" + str(result) + "' > " + folder + f + ".avrtime.o" + o)
            
            
