/*
Erik Morua
Nathan Azoulay
Program 4: Candy Factory
CS570 Operating Systems
*/
#ifndef __CandyFactory__
#define __CandyFactory__
#include <stdio.h>
#include <semaphore.h>
#include <string>
#include <pthread.h>
#include <iostream>
#include <queue>
using namespace std;
#define MILL 1000
#define NANO 1000000000

class CandyFactory {
private:
	//factory belt
	queue<string> belt;

	vector<struct factoryWorker> producers;
	vector<struct factoryWorker> consumers;
	int candyProduced;
	int candyConsumed;
	int numFrogs;
	int numSuckers;
	int numProducers;
	int numConsumers;
	sem_t resource;
	sem_t spaceOnBelt;
	sem_t empty;
	sem_t maxFrogs;

public:
	static const int TOT_LIMIT = 100;
	static const int BELT_LIMIT = 10;
	static const int FROG_LIMIT = 3;
	sem_t maxProducers;
	CandyFactory();

	bool addCandy(string type);
	string removeCandy(string type);

	//introduces new producers and consumers
	void addProducer(string type, int delay);
	void addConsumer(string type, int delay);
	//will gives us the number of candies on belt and delays
	void printBelt(string message);
	void productionInfo();
	void beginProduction();
};
//attributes
struct factoryWorker {
	string type;
	int work;
	int delay;
	int frogWork;
	int suckerWork;
	CandyFactory* factory;
	//semaphores
	sem_t* resource;
	sem_t* spaceOnBelt;
	sem_t* empty;
	sem_t* maxFrogs;
	sem_t* maxProducers;
};
#endif
