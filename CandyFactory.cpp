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
#include "io.h"
#include "CandyFactory.h"
#include "producer.h"
#include "production.h"
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
    ProductType res;
    
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
        res = FrogBite;
    }
    else{
        numSuckers++; 
        sumSuck++;
        res = Escargot;
    }
    int tmp[] = {numFrogs,numSuckers};
    int prod[] = {sumFrogs,sumSuck};
    io_add_type(res, tmp, prod);
    //printBelt("Added " + name);// keeping track of what is added on the belt.
   // cout << "  Produced: " << sumFrogs << " CFB + " << sumSuck << " EES = " << candyProduced << endl;
    return true;
}

//removes an item from the belt, similar to io_remove_type from io.cpp
string CandyFactory::removeCandy(string name){
    string product = "";
    ConsumerType foo; //struct defined in 'production.h'
    ProductType foo1; //struct containing products
    int candyOnBelt[] = {numFrogs,numSuckers}; //contains total on the belt at each step
    int candyConsumedLucy[] = {consumers[1].suckerWork+1,consumers[1].frogWork}; //using to pass for print formatting
    int candyConsumedEthel[] = {consumers[0].suckerWork+1,consumers[0].frogWork};
    if (candyConsumed > TOT_LIMIT) { //if consumed 100 items
        return "Quota";
    }
    string grabCandy = belt.front(); //grabs top item from the belt and consumes
    belt.pop();
    candyConsumed++; //total items consumed

    bool cfb = grabCandy.compare("crunchy frog bite") == 0; //check the type of candy that was consumed
    if (cfb) {
        numFrogs--; //keeping track of candy type consumed. 
        product = "crunchy frog bite";
        foo1 = FrogBite;
    }
    else {
        numSuckers--;
        product = "everlasting escargot sucker";
        foo1 = Escargot;
    }    
    if(name.compare("Lucy") == 0){ //checks to see which consumer took the candy off the belt, increments to the total amount consumed
        foo = Lucy;
        io_remove_type(foo, foo1, candyOnBelt,candyConsumedLucy);
    }
    else{
        foo = Ethel; //tydef struct in production.h
        io_remove_type(foo, foo1, candyOnBelt,candyConsumedEthel); // removes a candy from belt and prints it.
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
    int producedP[] = {producers[0].work, producers[1].work}; // number of each candy produced
    int ethel[] = {consumers[0].suckerWork , consumers[0].frogWork}; // number of candies of each type consumed by ethel
    int lucy[] = {consumers[1].suckerWork,consumers[1].frogWork }; // number of candies of each type consumed by lucy
    int *consumedP[] = {lucy,ethel};

    io_production_report(producedP, consumedP); //function in production.h
}



