all:
	g++ --std=c++11 main.cpp -o main
	./main
travis:
	g++ --std=c++11 main.cpp -O3 -o main
	./main < test.txt
