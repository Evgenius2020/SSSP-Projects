clean:
	rm -rf ./build

collect:
	mkdir build -p
	cp ./source/lifeRun/*.{cpp,h} ./build/
	cp ./source/matrixCompute/matrixCompute.{h,cpp} ./source/matrixCompute/squareCompute.cpp ./build/
	cp ./source/totalReduce/*.{cpp,h} ./build/
	cp ./source/main.cpp ./build/

build: collect
	g++ -std=c++11 ./build/*.cpp -I"./dependences/" ./dependences/msmpi86.lib -o ./build/main.exe

build64: collect
	g++ -std=c++11 ./build/*.cpp -I"./dependences/" ./dependences/msmpi64.lib -o ./build/main64.exe