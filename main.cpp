/*
Erik Morua, cssc3333, Red ID: 816670615
Nathan Azoulay, cssc3302 Red ID: 821871239
Program 4 Candy Factory
This program utilizes POSIX threads and semaphores to simulate a constantly updating belt in a candy factory. Two producers, 'Crunchy Frog bite' and 'Everlasting Escargot Sucker' and
Two consumers 'Lucy' and 'Ethel'. Given the rules of the program: The belt will continue to run until 100 candies have been produced at a rate input through command arguments.
Given delays to each producer and each consumer, the consumers will take an item off of the belt with a delay input through command arguments. 
Each add to the belt and consume from the belt prints a message containing info of the item added, and the consumer name and item consumed. Once 100 items have been consumed, the seperate
producer threads will terminate until both consumer threads are terminated. The termination of all threads will print information about the belt and consumers and exit.
USEAGE: 'make' To compile
		./mizzo -f 5 -e 15 -E 35 -L 20

Pair Programming Equitable Participation & Honesty Affidavit
We the undersigned promise that we have in good faith attempted to follow the principles of pair programming. Although we were free to discuss ides with others,
the implementation is our own. We have shared a common workspace and taken turns at the keyboard for the majority of the work that
we are submitting. Furthermore, any non programming portions of the assignment were done independently. We recognize that should this not be the case,
we will be subject to penalties as outlined in the course syllabus.

Pair Programmer 1  Nathan Azoulay, Red ID: 821871239, 4/15/2021
Pair Programmer 2  Erik Morua, Red ID: 816670615, 4/15/2021
*/
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <semaphore.h>
#include "parse.h"
#include "CandyFactory.h"
using namespace std;

//driver code 
int main(int argc, char* argv[]) {
	Parse parse;
	parse.parseLine(argc, argv);//parsing for delay time needed
	int timeEthel = parse.getEthel();
	int timeLucy = parse.getLucy();
	int timeFrog = parse.getFrog();
	int timeEscargot = parse.getSucker();
	CandyFactory factory; //factory instance to run our factory
	factory.addProducer("crunchy frog bite",timeFrog); //declaring producers, consumers
	factory.addProducer("everlasting escargot sucker",timeEscargot);
	factory.addConsumer("Ethel", timeEthel);
	factory.addConsumer("Lucy",timeLucy);
	factory.beginProduction(); //starting our belt
	sem_wait(&factory.maxProducers);

	factory.productionInfo();//print info
	
}