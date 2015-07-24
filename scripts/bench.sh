function fail
{
    echo "ERROR: $@"
    exit 1
}

DEFAULT_CFLAGS_mips=" -nostdlib -fno-exceptions -fno-rtti -static -fno-builtin -nostdinc"

TESTS=${TESTS:-ackermann.x array.x fib.x lists.x matrix.x sieve.x heapsort.x random.x}

if [ ! -d "benchmarks/bin" ]; then 
	mkdir "benchmarks/bin"; 
fi

for o in `seq 0 3` s; do
	if [ ! -d "benchmarks/bin/o${o}" ]; then 
		mkdir -p "benchmarks/bin/o${o}"; 
	fi
    echo ">>>>>>>>>>> Compilando a versão: ${o} <<<<<<<<<<";
    make clean
    make "CFLAGS_mips=${DEFAULT_CFLAGS_mips} -O${o}"
	cp benchmarks/models/*.x benchmarks/bin/o${o}
	
done
