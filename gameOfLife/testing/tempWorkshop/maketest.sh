# !bin/bash

./parser.exe $1

outName="prog_output.txt"
inName="test_input.txt"
prog_name="./life.exe"
vars=`cat test_input.txt`
array=( $vars )
    
procNum=${array[0]}
stepsLimit=${array[1]}
height=${array[2]}

mpirun -np $procNum $prog_name $stepsLimit $height $inName $outName
diff expected_output.txt $outName >> logs.txt
