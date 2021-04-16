/*
Erik Morua
Nathan Azoulay
Program 4: Candy Factory
CS570 Operating Systems
*/
#include "consumer.h"
#include "CandyFactory.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

//starting consumer threads
void* consume(void* num){
	factoryWorker* consumer = (factoryWorker*)num; //initializing 
	struct timespec tst;
	tst.tv_sec = consumer->delay / MILL;
	tst.tv_nsec = (consumer->delay % MILL) * (NANO / MILL);

	while (true) {
		nanosleep(&tst, NULL);
		sem_wait(consumer->empty);
		sem_wait(consumer->resource);
		string typeCandy = consumer->factory->removeCandy(consumer->type); //checks when removing an item
		sem_post(consumer->resource);

		if (typeCandy.compare("Quota") != 0) {
			sem_post(consumer -> spaceOnBelt); //check space on belt
			if (typeCandy.compare("crunchy frog bite") == 0) { //if consume a frog bite
				sem_post(consumer->maxFrogs);
				consumer->frogWork++; //increment frog bite
			}
			else {
				consumer->suckerWork++; //consumed everlasting escargot sucker
			}
			consumer->work++; //total consumed by consumer
		}
		else {
			pthread_exit(NULL); // releases thread
		}
	}

}