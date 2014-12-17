#include "multitape.h"

multitape::multitape(int numStates, string fileName, string input)
{
    m_numStates = numStates;
    //load input into first tape
    tapeOne.state = '0';
    tapeTwo.state = '0';

    //starting position
    tapeOne.position = 10;
    tapeTwo.position = 10;

    int size = input.size();
    for(int i = 0; i < 100; i++){ //load in 100 blank states and the input
        if(i >= 10 && i < (10+size)){
            tapeOne.tape.emplace_back(input[i-10]);
        }
        else{
            tapeOne.tape.emplace_back('_');
        }
    }
    for(int i = 0; i<100; i++){
        tapeTwo.tape.emplace_back('_');
    }
    readIn(fileName);
    run();
}

/*accept some file with states written
 *input into vector representing commands
 */
void multitape::readIn(string fileName){
    ifstream in (fileName.c_str());

    string line;
    bool first = true;
    vector<vector<char> > input;
    int numLines = 0;


    //read all input
    while(getline (in, line)){

        if(line == "") {break;}
        if(first){
            m_acceptingState = line[0];
            first = false;
        }
        else{
            numLines++;
            m_input.push_back(line);
       }

    }
    in.close();
}


// input:
// current state, current symbol, new symbol, movement, new state
/*
 *0: current state
 *1: current symbol
 *2: new symbol
 *3: movement
 *4: new state
*/

void multitape::run(){
   while(true){
        //autofail if states are not equal
        if(tapeOne.state != tapeTwo.state){
            cout << "Not accepted" << endl;
            return;
        }
        //check if positions are positive
        //positionCheck(positionOne, positionTwo);
        /*if(m_input[row].size()!=5){
            throw "Input is not formatted correctly";
        }*/

        //check States
        stateCheck();

        if(accept()){
            break;
        }
   }
}


/*
 *states:
 *inputs: 0 1 _
 *Movements: < (left) > (right) _ (stay)
*/

int multitape::move(int position, char direction){
    if(direction == '<'){
        return position-=1;
    }
    else if(direction == '>'){
        return position+=1;
    }
    else{
        return position;
    }
}


void multitape:: positionCheck(int &positionOne, int &positionTwo){
    if(positionOne < 0){
        tapeOne.tape.insert(tapeOne.tape.begin(), 0, 1);
        tapeOne.position = 0;
    }
    if(positionTwo < 0){
        tapeOne.tape.insert(tapeTwo.tape.begin(), 0, 1);
        positionTwo = 0;
    }
}

/*
 *0: current state
 *1: current symbol
 *2: new symbol
 *3: movement
 *4: new state
*/
void multitape::stateCheck(){
    int size = m_input.size();
    for(int i=0; i<size; i+=2){
        //if current state
        if(tapeOne.state == m_input[i][0] && tapeTwo.state == m_input[i+1][0]){
            char firstTape = tapeOne.tape[tapeOne.position];
            //cout << firstTape << endl;
            char secondTape = tapeTwo.tape[tapeTwo.position];
            //cout << secondTape << endl;
            //if current symbol
            if(firstTape == m_input[i][1] && secondTape == m_input[i+1][1]){
                //cout << m_input[i] << endl;
                //cout << m_input[i+1] << endl;
                //cout << "before: " << endl;
                //toString();
                //change char at position to new char
                tapeOne.tape[tapeOne.position] = m_input[i][2];
                tapeTwo.tape[tapeTwo.position] = m_input[i+1][2];

                //move
                tapeOne.position = move(tapeOne.position, m_input[i][3]);
                tapeTwo.position = move(tapeTwo.position, m_input[i+1][3]);

                //change state
                tapeOne.state = m_input[i][4];
                tapeTwo.state = m_input[i+1][4];
                //cout << "after" << endl;
                //toString();
                break;
            }

        }
    }
}
bool multitape::accept(){
    if(tapeOne.state == m_acceptingState){ //must be end of input
        cout << "Accepted!" << endl;
        return true;
    }
    else{ return false; }
}

void multitape::toString(){
    cout << tapeOne.position << endl;
    cout << tapeTwo.position << endl;
    cout << tapeOne.tape[tapeOne.position] << endl;
    cout << tapeTwo.tape[tapeTwo.position] << endl;
    cout << "stateOne: ";
    cout << tapeOne.state << endl;
    cout << "stateTwo: ";
    cout << tapeTwo.state << endl;
}
