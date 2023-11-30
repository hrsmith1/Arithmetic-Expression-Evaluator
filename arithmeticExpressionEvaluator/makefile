Calculator: main.o Evaluator.o
	g++ -std=c++11 -g -Wall main.o Evaluator.o -o Calculator

main.o: main.cpp Evaluator.h
	g++ -std=c++11 -g -Wall -c main.cpp

Evaluator.o: Evaluator.h Evaluator.cpp
	g++ -std=c++11 -g -Wall -c Evaluator.cpp 

clean: 
	rm *.o Calculator
