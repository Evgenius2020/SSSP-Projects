clean:
	rm -rf ./collected
	rm -rf ./build
	rm -rf ./build64	

collectDir:
	mkdir collected -p

buildDir:
	mkdir build -p

collect: collectDir collectMatrixCompute
	cp ./source/lifeRun/*.{cpp,h} ./collected/
	cp ./source/totalReduce/*.{cpp,h} ./collected/
	cp ./source/main.cpp ./collected/

collectBalanced: collectDir collectMatrixComputeBalanced
	cp ./source/lifeRun/*.{cpp,h} ./collected/
	cp ./source/totalReduce/*.{cpp,h} ./collected/
	cp ./source/main.cpp ./collected/

collectMatrixCompute:
	cp ./source/matrixCompute/matrixCompute.{h,cpp} ./source/matrixCompute/squareCompute.cpp ./collected/	

collectMatrixComputeBalanced:
	cp ./source/matrixCompute/matrixComputeBalansing.cpp ./source/matrixCompute/matrixCompute.h ./source/matrixCompute/squareCompute.cpp ./collected

build: buildDir
	g++ -std=c++11 ./collected/*.cpp -I"./dependences/" ./dependences/msmpi86.lib -o ./build/main.exe

build64: buildDir
	g++ -std=c++11 ./collected/*.cpp -I"./dependences/" ./dependences/msmpi64.lib -o ./build/main.exe

testsBuild: buildDir
	g++ -std=c++0x ./testing/parser.cpp -o ./build/parser.exe

testsClean:
	rm ./build/prog_output.txt ./build/test_input.txt ./build/logs.txt

testsRunBasic: testsBuild
	./testing/test.sh ./build/parser.exe ./build/main.exe ./testing/testCases/basic/full_field.txt