# !bin/bash

parsName=$1
progName=$2
testName=$3
./$parsName $testName
outName="prog_output.txt"
inName="test_input.txt"
inMatrix="inMatrix.txt"
vars=`cat $inName`
array=( $vars )

procNum=${array[0]}
stepsLimit=${array[1]}
height=${array[2]}

mpiexec -np $procNum ./$progName $stepsLimit $height $inMatrix $outName

result=`diff expected_output.txt $outName`

if [ -z "$result" ]
then
        echo "$testName ok" >> logs.txt
else
        echo "$testName bad" >> logs.txt
fi

