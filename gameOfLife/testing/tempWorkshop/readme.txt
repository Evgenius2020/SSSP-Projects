Testing system scheme:

1) testCase -> parser.exe -> input.txt, expected_output.txt
2) input.txt -> testing_program.exe -> real_output.txt
3) real_output.txt, expected_output.txt -> diff -> record to logs.txt
