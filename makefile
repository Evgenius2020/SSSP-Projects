clean:
	rm -rf ./collected
	rm -rf ./build
	rm -rf ./build64	

collectDir:
	mkdir collected -p

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

build:
	mkdir build -p
	g++ -std=c++11 ./collected/*.cpp -I"./dependences/" ./dependences/msmpi86.lib -o ./build/main.exe

build64:
	mkdir build64 -p
	g++ -std=c++11 ./collected/*.cpp -I"./dependences/" ./dependences/msmpi64.lib -o ./build64/main.exe