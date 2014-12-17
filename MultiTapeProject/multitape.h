#ifndef multitape_H
#define multitape_H

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <map>

using namespace std;

class multitape
{
public:
    struct turingTape{
        vector<char> tape;
        int position;
        char state;
    };
    
    //constructor
    multitape(int numStates, string fileName, string input);
    
    //reads in states from file
    void readIn(string fileName);
    
    //runs input program
    void run();
    
    //adjusts position
    int move(int position, char direction);
    
    //checks that position is not negative, and adjusts if it is
    void positionCheck(int &positionOne, int &positionTwo);

    //combs through input and looks at all possible states
    void stateCheck();
    
    bool accept();
    
    void toString();

private:
    int m_numStates;
    char m_acceptingState;
    
    //vector of different states/transitions
    vector<string> m_input;
    //map <int, vector<string> > states;
    
    turingTape tapeOne;
    turingTape tapeTwo;


};


#endif // multitape_H
