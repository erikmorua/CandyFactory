/*
Erik Morua
Nathan Azoulay
Program 4: Candy Factory
CS570 Operating Systems
*/
#include "parse.h"
#include <iostream>
#include <cstdlib>
#include <getopt.h>
using namespace std;


void Parse::parseLine(int argc, char* argv[]) {
	timeEthel=timeLucy=timeFrog=timeSucker=0;
	int option;

	while ((option = getopt(argc, argv, "f:e:E:L:")) != -1) {
		switch (option) {
		case 'f': //-f timeFrog number of MS requires to produce each crunchy frog bite
			f_FLAG = true;
			timeFrog = atoi(argv[2]);

			break;
		case 'e': //-e timeSucker number of Ms required to produce each everlasting escargot sucker
			e_FLAG = true;
			timeSucker = atoi(argv[4]);
			break;
		case 'E': //number of ms that ethel consumer requires to put a candy in the box. put thread to sleep for timeEthel
			E_FLAG = true;
			if (argv[6] != NULL) { // if not default
				timeEthel = atoi(argv[6]); //time to sleep for ethel in milliseconds
			}
			else { //default, no delay, no time to sleep for ethel thread
				timeEthel = 0;
			}
			break;
		case 'L': //same as Ethel
			L_FLAG = true;
			if (timeEthel != 0) { // no default on ethel
				if (argv[8] != NULL) { // no default on lucy
					timeLucy = atoi(argv[8]);
				}
				else { // default on lucy, no delay, no sleep
					timeLucy = 0;
				}
			}
			else { //default on lucy
				if (argv[7] != NULL) {// no default on lucy
					timeLucy = atoi(argv[7]);
				}
				else { // default on lucy
					timeLucy = 0;
				}
			}
			break;
		default: //not enough parameters
			exit(1);
		}
		
	} // end while loop	
	
} // end parseLine()

int Parse::getLucy()
{
	return this->timeLucy;
}

int Parse::getEthel()
{
	return this->timeEthel;
}

int Parse::getFrog()
{
	return this->timeFrog;
}

int Parse::getSucker()
{
	return this->timeSucker;
}