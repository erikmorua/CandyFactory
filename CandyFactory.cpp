/*
Erik Morua
Nathan Azoulay
Program 4: Candy Factory
CS570 Operating Systems
*/
#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <queue>
#include "CandyFactory.h"
#include "producer.h"
#include "consumer.h"
using namespace std;

int sumFrogs, sumSuck = 0;

//intializing semaphores needed 
CandyFactory::CandyFactory(){
    sem_init(&resource,0,1);
    sem_init(&spaceOnBelt,0,BELT_LIMIT);
    sem_init(&empty,0,0);
    sem_init(&maxFrogs,0,FROG_LIMIT);
    sem_init(&maxProducers,0,0);
    candyProduced = candyConsumed = 0; //total items put on belt and taken off
    numFrogs = numSuckers = numProducers = numConsumers = 0;
}

//adds a new producer
void CandyFactory::addProducer(string type,int delay){
    factoryWorker producer = {type,0,delay,0,0,this,&resource,&spaceOnBelt,&empty,&maxFrogs,&maxProducers};
    producers.push_back(producer);
    numProducers++;
}

//new consumer
void CandyFactory::addConsumer(string type,int delay){
    factoryWorker consumer = {type,0,delay,0,0,this,&resource,&spaceOnBelt,&empty,&maxFrogs,&maxProducers};
    consumers.push_back(consumer);
    numConsumers++;
}

//begins threads for candy factory
void CandyFactory::beginProduction(){
    for(int i=0; i < (signed)producers.size();i++){ //starts number of producer threads needed
        factoryWorker *thr = &producers[i];
        pthread_t itemProducer;
        pthread_create(&itemProducer,NULL,produce,(void*)thr);
    }
    for(int i=0; i< (signed)consumers.size();i++){ //starts number of consumer threads needed
        factoryWorker *thr = &consumers[i];
        pthread_t itemConsumer;
        pthread_create(&itemConsumer,NULL,consume,(void*)thr);
    }
}
int sumCFB = 0;
int sumEES = 0;
//name = type of candy added, return true if successful else false if at capacity.
bool CandyFactory::addCandy(string name){
    
    //check if you can add more candies to the belt
    if(candyProduced >= TOT_LIMIT){
        return false;
    }
    belt.push(name); //if < 100 items on belt, push a new candy
    candyProduced++;

    //check the type of candy added
    if (name.compare("crunchy frog bite") == 0){
        numFrogs++;
        sumFrogs++;
    }
    else{
        numSuckers++; 
        sumSuck++;
    }
    printBelt("Added " + name);// keeping track of what is added on the belt.
    cout << "  Produced: " << sumFrogs << " CFB + " << sumSuck << " EES = " << candyProduced << endl;
    return true;
}

//removes an item from the belt, similar to io_remove_type from io.cpp
string CandyFactory::removeCandy(string name){
    if (candyConsumed > TOT_LIMIT) { //if consumed 100 items
        return "Quota";
    }
    string grabCandy = belt.front(); //grabes the top item from the belt and consumes
    belt.pop();
    candyConsumed++; //total items consumed

    bool cfb = grabCandy.compare("crunchy frog bite") == 0; //check the type of candy that was consumed
    if (cfb) {
        numFrogs--; //keeping track of candies consumed 
    }
    else {
        numSuckers--;
    }
    printBelt(name + " consumed " + (cfb ? "crunchy frog bite" : "everlasting escargot sucker") + ". "); //print each time a consumer eats a candy
    
    if(name.compare("Lucy") == 0){ //checks to see which consumer took the candy off the belt, increments to the total amount consumed
        cout << "Lucy totals: " << consumers[1].suckerWork+1  << " CFB + " << consumers[1].frogWork << " EES = " << consumers[1].work+1 <<endl;
    }
    else{
        cout << "Ethel totals: " << consumers[0].suckerWork+1  << " CFB + " << consumers[0].frogWork << " EES = " << consumers[0].work+1 << endl;
    }
    if (candyConsumed >= TOT_LIMIT) { //check total candies consumed for semaphore
        sem_post(&maxProducers);
    }
    return grabCandy;
}

void CandyFactory::printBelt(string message) { //format printing
    cout << "Belt: " << numFrogs << " CFB + " << numSuckers << " EES = " << numFrogs + numSuckers << ".  " << message;
    
}


/*printing results*/
void CandyFactory::productionInfo() {
    cout << "\nProduction Report" << endl;
    cout << "-------------------" << endl;

    for (int i = 0; i < (signed)producers.size(); i++) { //printing totals for each producer
        cout << producers[i].type << " producer generated " << producers[i].work << " candies" << endl;
    }
    for (int i = 0; i < (signed)consumers.size(); i++) { // printing for each consumer
        cout << consumers[i].type << " consumed " << consumers[i].suckerWork << " " << " CFB" << " + " << consumers[i].frogWork << " " << " EES"
            << " = " << consumers[i].work << " total" << endl;
    }
}



