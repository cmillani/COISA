function fail
{
    echo "ERROR: $@"
    exit 1
}

DEFAULT_COMPILER="gcc"
DEFAULT_CFLAGS_i386="-DARCH=1"

PERF=${PERF:-`which perf`} 
TIME=${TIME:-`which gtime`}
if [ -z "$TIME" ]; then
	TIME=${TIME:-`which time`}
fi

PROG=${PROG:-./bin/microvm}
NUMBER_OF_TESTS=1
TESTS=${TESTS:-ackermann.x array.x fib.x lists.x matrix.x sieve.x heapsort.x random.x}

rm tests/*o1 tests/*o2 tests/*o3 tests/*os

for o in `seq 0 3` s; do
    
	if [ -n "$PERF" ]; then
		echo ">>>>>>>>>>>> Compilando a versão: ${f} HOST 1<<<<<<<<<<<<";

	    make clean_vm
	    make i386 "CFLAGS_i386=${DEFAULT_CFLAGS_i386} -DMEASURING=0 -DRUN_VM=0"
		
		echo ">>>>>>>>>>>> Rodando sem a CPU para contagem <<<<<<<<<<<<";
		for f in ${TESTS}; do
		
		    echo ">>>>>>>>>>> Iniciando o teste da versão: ${f} <<<<<<<<<<<";
		    for i in `seq 1 $NUMBER_OF_TESTS`; do
		        echo "$i/$NUMBER_OF_TESTS"

		        out4=$(($PERF stat -e instructions:u -x $PROG benchmarks/models/${f} >> /dev/null) 2>&1 | grep instruction | cut -d '.' -f1)
			echo $out4
		        echo $out4 >> tests/${f}.host1.o${o}

		    done

		    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
		    echo 
		done
		
		echo ">>>>>>>>>>>> Compilando a versão: ${f} HOST 2<<<<<<<<<<<<";

	    make clean_vm
	    make i386 "CFLAGS_i386=${DEFAULT_CFLAGS_i386} -DMEASURING=0 -DRUN_VM=1"
		
		echo ">>>>>>>>>>>> Rodando sem a CPU para contagem <<<<<<<<<<<<";
		for f in ${TESTS}; do
		
		    echo ">>>>>>>>>>> Iniciando o teste da versão: ${f} <<<<<<<<<<<";
		    for i in `seq 1 $NUMBER_OF_TESTS`; do
		        echo "$i/$NUMBER_OF_TESTS"
		
		        out5=$(($PERF stat -e instructions:u -x $PROG benchmarks/models/${f} >> /dev/null) 2>&1 | grep instruction | cut -d '.' -f1)
			echo $out5
		        echo $out5 >> tests/${f}.host2.o${o}

		    done

		    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
		    echo 
		done
	fi
done
