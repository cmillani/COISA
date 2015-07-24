function fail
{
    echo "ERROR: $@"
    exit 1
}


NUMBER_OF_TESTS=100
# TESTS=${TESTS:-ackermann.x array.x fib.x matrix.x sieve.x heapsort.x random.x}
TESTS=${TESTS:-matrix.x sieve.x heapsort.x random.x}

echo ">>>>>>>>>>> Compilando a versão: ${f} Testing <<<<<<<<<<<";
#o MEASURING=1 habilita a contagem do tempo utilizando o clock()
make clean
make i386 "CFLAGS_i386=${DEFAULT_CFLAGS_i386} -DMEASURING=1 -Os"


for f in ${TESTS}; do
	
    echo ">>>>>>>>>>> Iniciando o teste da versão: ${f} <<<<<<<<<<<";
    for i in `seq 1 $NUMBER_OF_TESTS`; do
        echo "$i/$NUMBER_OF_TESTS"
        out3=$((python arduino_loader.py ../benchmarks/bin/os/${f}) | grep -a TIMESPENT | cut -d '.' -f2)
		echo $out3
        echo $out3 >> ../tests/${f}.time.os

    done

    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
    echo "\n"
done
