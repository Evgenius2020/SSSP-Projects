.PHONY: build

clean:
	rm -rf ./collected
	rm -rf ./build

collectDir:
	mkdir collected -p

buildDir:
	mkdir build -p

collect: collectDir
	cp ./source/lifeRun/*.{cpp,h} ./collected/
	cp ./source/totalReduce/*.{cpp,h} ./collected/
	cp ./source/matrixCompute/matrixCompute.{h,cpp} ./source/matrixCompute/squareCompute.cpp ./collected/		
	cp ./source/main.cpp ./collected/

collectBalancing: collectDir
	cp ./source/lifeRun/*.{cpp,h} ./collected/
	cp ./source/totalReduce/*.{cpp,h} ./collected/
	cp ./source/main.cpp ./collected/
	cp ./source/matrixCompute/{matrixComputeBalancing.cpp,matrixCompute.h,squareCompute.cpp} ./collected

build: buildDir
	g++ -std=c++0x ./collected/*.cpp -I"./dependences/" ./dependences/msmpi86.lib -o ./build/main.exe

build64: buildDir
	g++ -std=c++0x ./collected/*.cpp -I"./dependences/" ./dependences/msmpi64.lib -o ./build/main.exe

testBuild: buildDir
	g++ -std=c++0x ./testing/parser.cpp -o ./build/parser.exe

testClean:
	rm ./build/prog_output.txt ./build/test_input.txt ./build/logs.txt