# !bin/bash

./run_test.exe $1

outName="prog_output.txt"
inName="test_input.txt"
prog_name="game_of_life.exe"
vars=`cat test_input.txt`
array=( $vars )
    
procNum=${array[0]}
stepsLimit=${array[1]}
height=${array[2]}

mpicxx -np$procNum $prog_name $stepsLimit $height $inName $outName
diff expected_output.txt $outName >> logs.txt
