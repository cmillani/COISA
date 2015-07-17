function fail
{
    echo "ERROR: $@"
    exit 1
}

DEFAULT_COMPILER="gcc"
DEFAULT_CFLAGS_i386="-DARCH=1 -DRUN_VM=1"
DEFAULT_CFLAGS_mips=" -nostdlib -fno-exceptions -fno-rtti -static -fno-builtin -nostdinc"


PERF=${PERF:-`which perf`} 
TIME=${TIME:-`which gtime`}
if [ -z "$TIME" ]; then
	TIME=${TIME:-`which time`}
fi
PROG=${PROG:-./bin/microvm}
NUMBER_OF_TESTS=1
TESTS=${TESTS:-ackermann.x array.x fib.x lists.x matrix.x sieve.x}

rm tests/*o1 tests/*o2 tests/*o3 tests/*os

for o in `seq 0 3` s; do
    echo ">>>>>>>>>>> Compilando a versão: ${f} Counting <<<<<<<<<<";
	# o COUNTING=1 habilita a contagem das instrucoes na VM
    make clean
    make "CFLAGS_i386=${DEFAULT_CFLAGS_i386} -DCOUNTING=1" "CFLAGS_mips=${DEFAULT_CFLAGS_mips} -O${o}"
	
	for f in ${TESTS}; do
		

	    echo ">>>>>>>>>>> Iniciando o count da versão: ${f} <<<<<<<<<<<";
		#Conta as instrucoes
        out=$(($PROG benchmarks/models/${f}) | grep ç | cut -d'ç' -f2)
        echo $out > tests/${f}.count.o${o}
		#Verifica o tamanho o binario
		out2=$(ls -l benchmarks/models/${f})
		echo $out2 | cut -d' ' -f5 > tests/${f}.size.o${o}

	    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
	    echo "\n"
	done
	
	echo ">>>>>>>>>>> Compilando a versão: ${f} Testing <<<<<<<<<<<";
	#o MEASURING=1 habilita a contagem do tempo utilizando o clock()
    make clean
    make "CFLAGS_mips=${DEFAULT_CFLAGS_mips} -O${o}" "CFLAGS_i386=${DEFAULT_CFLAGS_i386} -DMEASURING=1"
	
	for f in ${TESTS}; do
		
	    echo ">>>>>>>>>>> Iniciando o teste da versão: ${f} <<<<<<<<<<<";
	    for i in `seq 1 $NUMBER_OF_TESTS`; do
	        echo "$i/$NUMBER_OF_TESTS"
	        out3=$(($PROG benchmarks/models/${f}) | grep ç | cut -d'ç' -f2)
			echo $out3
			echo $o
	        echo $out3 >> tests/${f}.time.o${o}

	    done

	    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
	    echo "\n"
	done
done