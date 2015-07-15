function fail
{
    echo "ERROR: $@"
    exit 1
}

CWPROOT=$HOME/src/cwp
PATH=$CWPROOT/bin:$PATH

DEFAULT_COMPILER="gcc"
DEFAULT_CFLAGS_i386="-DCOUNTING=1"
DEFAULT_CFLAGS_mips="-nostdlib -fno-exceptions -fno-rtti -static"


TIME=${TIME:-`which gtime`}
PROG=${PROG:-./bin/microvm}
NUMBER_OF_TESTS=1
TESTS=${TESTS:-ackermann.x array.x fib.x lists.x matrix.x sieve.x}

rm tests/*o1 tests/*o2 tests/*o3 tests/*os

for o in `seq 0 3` s; do
    echo ">>>>>>>>>>> Compilando a versão: ${f} Counting <<<<<<<<<<";

    make clean
    make "CFLAGS_i386=${DEFAULT_CFLAGS_i386}" "CFLAGS_mips=${DEFAULT_CFLAGS_mips} -O${o}"
	
	for f in ${TESTS}; do
		

	    echo ">>>>>>>>>>> Iniciando o count da versão: ${f} <<<<<<<<<<<";
		
        out=$($PROG benchmarks/models/${f})
        echo $out | cut -d'ç' -f2  > tests/${f}.count.o${o}
		
		out2=$(ls -l benchmarks/models/${f})

		echo $out2 | cut -d ' ' -f5 > tests/${f}.size.o${o}

	    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
	    echo "\n"
	done
	
	echo ">>>>>>>>>>> Compilando a versão: ${f} Testing <<<<<<<<<<<";

    make clean
    make "CFLAGS_mips=${DEFAULT_CFLAGS_mips} -O${o}"
	
	for f in ${TESTS}; do
		
	    echo ">>>>>>>>>>> Iniciando o teste da versão: ${f} <<<<<<<<<<<";
	    for i in `seq 1 $NUMBER_OF_TESTS`; do
	        echo "$i/$NUMBER_OF_TESTS"

	        out=$(($TIME -f "%e:%U:%S:%M" $PROG benchmarks/models/${f}) 2>&1 >/dev/null)
	        echo $out | cut -d':' -f1 >> tests/${f}.real.o${o}
	        echo $out | cut -d':' -f2 >> tests/${f}.user.o${o}
	        echo $out | cut -d':' -f3 >> tests/${f}.sys.o${o}
	        echo $out | cut -d':' -f4 >> tests/${f}.mem.o${o}

	    done

	    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
	    echo "\n"
	done
done