# !bin/bash

parsName=$1
progName=$2
testName=$3
./$parsName $testName
outName="output.txt"
inName="test_input.txt"
vars=`cat $inName`
array=( $vars )

procNum=${array[0]}
stepsLimit=${array[1]}
height=${array[2]}

mpirun -np $procNum ./$progName $stepsLimit $height $inName $outName

result=`diff expected_output.txt $outName`

if [ -z "$result" ]
then
        echo "$testName ok" >> logs.txt
else
        echo "$testName bad" >> logs.txt
fi

