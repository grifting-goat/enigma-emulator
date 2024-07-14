#include <iostream>
#include <string>
using namespace std;

//rotors and reflector
char rotorSet[26][5] = {
    {'t', 'r', 'o', 'b', 'y'},
    {'c', 'l', 'k', 'u', 'e'},
    {'g', 's', 'p', 'n', 'w'},
    {'j', 'q', 'a', 'z', 'h'},
    {'z', 'g', 'v', 't', 'o'},
    {'f', 'w', 's', 'i', 'n'},
    {'w', 'd', 'c', 'l', 'x'},
    {'b', 'm', 'e', 'g', 'l'},
    {'p', 'k', 'x', 'y', 'u'},
    {'d', 'a', 'r', 'v', 's'},
    {'r', 'j', 'q', 'f', 'd'},
    {'v', 'h', 'j', 'o', 'c'},
    {'y', 'p', 'i', 'k', 't'},
    {'x', 'o', 'm', 'r', 'q'},
    {'e', 'n', 'b', 'h', 'v'},
    {'m', 'i', 'z', 'a', 'j'},
    {'h', 'y', 'g', 'p', 'k'},
    {'a', 'v', 't', 'q', 'z'},
    {'s', 'x', 'd', 'c', 'b'},
    {'u', 'e', 'w', 'm', 'f'},
    {'q', 'c', 'f', 'd', 'r'},
    {'i', 'f', 'u', 'j', 'p'},
    {'l', 'b', 'n', 'w', 'a'},
    {'k', 't', 'l', 'e', 'i'},
    {'o', 'u', 'h', 'x', 'g'},
    {'n', 'z', 'y', 's', 'm'}
};
char reflector[26] = {'l', 'a', 'g', 'p', 's', 'e', 'j', 'f', 'z', 't', 'm', 'q', 'd', 'o', 'y', 'v', 'i', 'x', 'k', 'h', 'w', 'c', 'r', 'b', 'n', 'u'};

//function inits
void enigmaCode(char &c, char plugs[26], int rotors[3],int intialNum[3]);
void plugBoard(char &c, char plugs[26]);
void rotorEncode(char &c, int rotor, int offset);
void enigmaBack(char &c, char plugs[26], int rotors[3], int intialNum[3]);
void rotorDecode(char &c, int rotor, int offset);

//translates a string to or from enigma code
string enigmaEncode(string str, char plugs[26], int rotors[3], int startSet[3]) {
    string s = str; // copies string
    int intialNum[3] = {startSet[0],startSet[1],startSet[2]}; // copies staring positions
    //iterate and encode each character
    for(char &c : s) {
        if (c <= 122 && c >= 97 ) {
            enigmaCode(c, plugs, rotors, intialNum);
        }
        else {
            c = ' ';
        }
    }  
    return s;
    
}
//encodes a single character
void enigmaCode(char &c, char plugs[26], int rotors[3], int intialNum[3]) {
    plugBoard(c, plugs);
    // go trhough the 3 rotors
    for(int i = 0; i < 3; i++) {
        rotorEncode(c, rotors[i], intialNum[i]);
    }
    //reflection
    c = reflector[(c-'a')];
    // go back through the rotors
    for(int i = 2; i >= 0; i--) {
        rotorEncode(c, rotors[i], intialNum[i]);
    }
    plugBoard(c, plugs);
    intialNum[0]++;
    if (intialNum[0] % 26 == 0) {
        intialNum[1]++;
        if (intialNum[1] % 26 == 0) {
            intialNum[2]++;
        }
    }
}
//switches a character based on which plugs are activated
void plugBoard(char &c, char plugs[26]) {
    c = plugs[(c-'a')];

}
//runs the character through a rotor
void rotorEncode(char &c, int rotor, int offset) {
    c = rotorSet[((c-'a')+offset)%26][rotor];

}

//decoding
string enigmaDecode(string str, char plugs[26], int rotors[3], int startSet[3]) {
    string s = str;
    int intialNum[3] = {startSet[0],startSet[1],startSet[2]};
    //iterate and encode each character
    for(char &c : s) {
        if (c <= 122 && c >= 97 ) {
            enigmaBack(c, plugs, rotors, intialNum);
        }
        else {
            c = ' ';
        }
    }
    return s;
    
}
void enigmaBack(char &c, char plugs[26], int rotors[3], int intialNum[3]) {
    plugBoard(c, plugs);
    // go trhough the 3 rotors
    for(int i = 0; i < 3; i++) {
        rotorDecode(c, rotors[i],intialNum[i]);
    }
    //reflection
    for (int i = 0; i < 26; i++ ) {
        if (c == reflector[i]) {
            c = i + 'a';
            break;
        }
    }
    // go back through the rotors
    for(int i = 2; i >= 0 ; i--) {
        rotorDecode(c, rotors[i], intialNum[i]);
    }
    plugBoard(c, plugs);
    intialNum[0]++;
    if (intialNum[0] % 26 == 0) {
        intialNum[1]++;
        if (intialNum[1] % 26 == 0) {
            intialNum[2]++;
        }
    }
}
//decodes through a single rotor
void rotorDecode(char &c, int rotor, int offset) {
    for (int i = 0; i < 26; i++ ) {
        if (c == rotorSet[(i+offset)%26][rotor]) {
            c = i + 'a';
            break;
        }
    }

}
void test() {
    char pluh[] = { 
    'b', 'a', 'c', 'd', 'o', 'f', 'g', 'h', 'i', 'j', 
    'k', 'l', 'm', 'n', 'e', 'p', 'q', 'r', 't', 's', 
    'u', 'v', 'w', 'x', 'y', 'z' 
    };
    int rotors[3] = {0,1,2};
    int intialNum[3] = {0, 0, 0};
    string s = "turingiscoolandall";
    string news = enigmaEncode(s, pluh, rotors, intialNum);
    cout << news << "\n";
    cout << s << "\n";
    cout << enigmaDecode(news, pluh, rotors, intialNum) << "\n";
}

void interface() {
    //variables
    char plugBoard[] = { 
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
    'u', 'v', 'w', 'x', 'y', 'z' 
    }; //defines a plug board with no letters switched
    char tweet[280];
    int rotors[3] = {0,1,2}; //which rotors usesd
    int intialNum[3] = {0, 0, 0}; //intial starting config
    bool bDirection; //determines wether to encode a phrase or decode it
    bool bCheck;
    int nRotNum;
    int plugCount;

    //grabs the message to encode/decode
    cout << "Message: ";
    cin.get(tweet, 280);

    //determinds which way to go
    cout << "Would you like to encode or decode a message? (1 for decode and 0 for encode)";
    cin >> bDirection;

    //asks the user for rotor
    cout << "which rotors would you like to use? numbered 1-5:" << endl;
    cout << "First: ";
    cin >> nRotNum;
    if (nRotNum <= 5 && nRotNum >= 1) {rotors[0] = nRotNum-1;}
    cout << "Second: ";
    cin >> nRotNum;
    if (nRotNum <= 5 && nRotNum >= 1) {rotors[1] = nRotNum-1;}
    cout << "Third: ";
    cin >> nRotNum;
    if (nRotNum <= 5 && nRotNum >= 1) {rotors[2] = nRotNum-1;}

    //set intial rotor positions
    cout << "For each rotor, what is the starting orientation numbered 1-26: " << endl;
    cout << "First: ";
    cin >> nRotNum;
    if (nRotNum <= 26 && nRotNum >= 01) {intialNum[0] = nRotNum-1;}
    cout << "Second: ";
    cin >> nRotNum;
    if (nRotNum <= 26 && nRotNum >= 1) {intialNum[1] = nRotNum-1;}
    cout << "Third: ";
    cin >> nRotNum;
    if (nRotNum <= 26 && nRotNum >= 1) {intialNum[2] = nRotNum-1;}

    //modify plug board
    cout << "How many plugs to use? 0-10: ";
    cin >> plugCount;
    for (int i = 0; i < plugCount; i++) {
        char cSwitch; char cWith;
        cout << i + 1 << ":" << endl;
        cout << "Switch:" << endl;
        cin >> cSwitch;
        cout << "With:" << endl;
        cin >> cWith;
        plugBoard[cSwitch-'a'] = cWith;
        plugBoard[cWith-'a'] = cSwitch;
        cout << endl;

    }

    string str(tweet);
    string news = bDirection ? enigmaDecode(str, plugBoard, rotors, intialNum) : enigmaEncode(str, plugBoard, rotors, intialNum);
    cout << news << endl;
    cout << "Test to ensure? (1 for yes and 0 for no)";
    cin >> bCheck;
    if(bCheck) {
        news = !bDirection ? enigmaDecode(news, plugBoard, rotors, intialNum) : enigmaEncode(news, plugBoard, rotors, intialNum); 
        cout << news << endl;
    }
}

int main() {
    interface();
    return 0;
}