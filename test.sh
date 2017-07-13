# !bin/bash

parsName="./build/parser.exe"
progName="./build/main.exe"
foldName="./build/"
testsPath="./testing/testCases/**/*.txt"
echo "=================" >> foldName/logs.txt
for testName in `ls $testsPath` ; do
        $parsName $testName $foldName
        outName=$foldName"prog_output.txt"
        inName=$foldName"test_input.txt"
        inMatrix=$foldName"inMatrix.txt"
        vars=`cat $inName`
        array=( $vars )

        procNum=${array[0]}
        stepsLimit=${array[1]}
        height=${array[2]}

        mpiexec -np $procNum ./$progName $stepsLimit $height $inMatrix $outName

        result=`diff $foldName'expected_output.txt' $outName`

        if [ -z "$result" ]
        then
                echo "$testName passed" >> $foldName'logs.txt'
                echo "$testName passed"                
        else
                echo "$testName failed" >> $foldName'logs.txt'
                echo "$testName failed"                
        fi; 
done