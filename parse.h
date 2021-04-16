/*
Erik Morua
Nathan Azoulay
Program 4: Candy Factory
CS570 Operating Systems
*/
#ifndef __parse__
#define __parse__

//declaring times needed ot parse
class Parse {
private:
    int timeLucy;
    int timeEthel;
    int timeFrog;
    int timeSucker;
    

public: //getters and flag declarations
    void parseLine(int argc, char* argv[]);
    int getLucy();
    int getEthel();
    int getFrog();
    int getSucker();
    bool E_FLAG = false;
    bool L_FLAG = false;
    bool f_FLAG = false; 
    bool e_FLAG = false;
};

#endif