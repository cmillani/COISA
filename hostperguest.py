import os

optimizations = ["0","1","2","3","s"]
# optimizations = ["0"]
files = ["ackermann.x", "array.x", "fib.x", "lists.x", "matrix.x", "sieve.x", "heapsort.x", "random.x"]
# files = ["a.x"]
count = 25

for o in optimizations:
	for f in files:
		filename1 = "tests/" + f + ".host1.o" + o
		filename2 = "tests/" + f + ".host2.o" + o
		filename3 = "tests/" + f + ".count.o" + o
		file1 = open(filename1, 'r')
		file2 = open(filename2, 'r')
		file3 = open(filename3, 'r')
		highest1 = 0.0
		highest2 = 0.0
		for i in range(count):
			temp1 = int(file1.readline())
			if temp1 > highest1:
				highest1 = temp1 
			temp2 = int(file2.readline())
			if temp2 > highest2:
				highest2 = temp2
		pure = highest1
		complete = highest2
		vm = int(file3.readline())
		result = (complete-pure)/float(vm)
		print result
		os.system("echo '" + str(result) + "' > tests/" + f + ".bpg.o" + o)
            
            
