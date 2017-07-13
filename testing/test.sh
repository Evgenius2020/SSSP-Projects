# !bin/bash

parsName=$1
progName=$2
foldName=$3
testPath="./testing/testCases/$foldName/"
for r in `ls $testPath` ; do 
        testName=$(echo $r) 
        $parsName $testPath$testName
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
                echo "$testName passed" >> ./logs.txt
                echo "$testName passed"                
        else
                echo "$testName failed" >> ./logs.txt
                echo "$testName failed"                
        fi; 
done


