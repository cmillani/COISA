function fail
{
    echo "ERROR: $@"
    exit 1
}

CWPROOT=$HOME/src/cwp
PATH=$CWPROOT/bin:$PATH

# DEFAULT_COMPILER="gcc"
# DEFAULT_CFLAGS="-O3 -std=gnu99 -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -fopenmp"
# DEFAULT_LFLAGS="-fopenmp -lm"

# DEFAULT_COMPILER=icc
# DEFAULT_CFLAGS="-O3 -std=c99 -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -openmp -xhost -restrict -fno-exceptions -opt-streaming-stores=never -ipo2 -static"
# DEFAULT_LFLAGS="-openmp -lm"

TIME=${TIME:-`which time`}
DATA=${DATA:-../simple-synthetic.su}
ARGS=${ARGS:-"1.98e-7 1.77e-6 101 600 0.002"}
PROG=${PROG:-./cmp.x}
NUMBER_OF_TESTS=1
TESTS=( v08 )

rm tests/*user tests/*sys tests/*real tests/*mem

for f in "${TESTS[@]}"; do
    echo ">>>>>>>>>>>>>>> Compilando a versão: ${f} <<<<<<<<<<<<<<<";
    cd ${f}
    make clean
    make "CC=${DEFAULT_COMPILER}" "CFLAGS=${DEFAULT_CFLAGS}" "LFLAGS=${DEFAULT_LFLAGS}"

    echo "\n"
    echo ">>>>>>>>>>> Iniciando o teste da versão: ${f} <<<<<<<<<<<";
    for i in `seq 1 $NUMBER_OF_TESTS`; do
        echo "$i/$NUMBER_OF_TESTS"
        # out=$($TIME $PROG $ARGS $DATA 2>&1 >/dev/null)
        # echo $out | cut -d' ' -f2 | cut -c3-7 >> ../tests/${f}.real
        # echo $out | cut -d' ' -f4 | cut -c3-7 >> ../tests/${f}.user
        # echo $out | cut -d' ' -f6 | cut -c3-7 >> ../tests/${f}.sys

        out=$(($TIME -f "%e:%U:%S:%M" $PROG $ARGS $DATA) 2>&1 >/dev/null)
        echo $out | cut -d':' -f1 >> ../tests/${f}.real
        echo $out | cut -d':' -f2 >> ../tests/${f}.user
        echo $out | cut -d':' -f3 >> ../tests/${f}.sys
        echo $out | cut -d':' -f4 >> ../tests/${f}.mem

        # Verificando se o resultado do programa é válido.
        # sucmp --silent ../cmp.coher.su ./cmp.coher.su || echo "cmp.coher.su inválido"
        # sucmp --silent ../cmp.stack.su ./cmp.stack.su || echo "cmp.stack.su inválido"
        # sucmp --silent ../c.su ./c.su                 || echo "c.su inválido"
    done

    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
    echo "\n"
    cd ..
done