/*
Erik Morua
Nathan Azoulay
Program 4: Candy Factory
CS570 Operating Systems
*/
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <semaphore.h>
#include "producer.h"
#include "CandyFactory.h"
#include <stdio.h>
#include <time.h>

//begins thread for producers
void* produce(void* num) {
	factoryWorker *producer = (factoryWorker*)num;
	struct timespec tst;
	tst.tv_sec = producer->delay / MILL;
	tst.tv_nsec = (producer->delay % MILL) * (NANO/MILL);
	bool isCfb = (producer->type.compare("crunchy frog bite")==0);
	
	while (true) {
		nanosleep(&tst, NULL);

		if(isCfb) {
			sem_wait(producer->maxFrogs); // checking for max frogs on belt
		}
		sem_wait(producer->spaceOnBelt); //check for belt < 100

		sem_wait(producer->resource);
		bool check = (producer->factory->addCandy(producer->type)); // critical section
		sem_post(producer->resource);

		if(check){
			sem_post(producer->empty);
			producer->work++;
			if(isCfb){
				producer->frogWork++; //increments number of frogs added by producer
			}
			else{
				producer->suckerWork++;//number of everlasting escargot suckers added by consumer
			}
		}
		else{
			pthread_exit(NULL); //once done, release thread
		}
	}

}