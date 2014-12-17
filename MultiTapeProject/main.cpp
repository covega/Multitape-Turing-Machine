#include <iostream>
#include "multiTape.h"

using namespace std;

int main()
{
    string file = "palindrome.txt";
    string input;
    int numStates = 5;
    while(true){
        cout << "input?" << endl;
        cin >> input;
        multitape tape(numStates, file, input);
    }
    return 0;
}


