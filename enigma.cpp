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

int main() {
    //test();
    char pluh[] = { 
    'b', 'a', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 't', 's', 
    'u', 'v', 'w', 'x', 'y', 'z' 
    };
    char tweet[280];
    int rotors[3] = {0,1,2};
    int intialNum[3] = {0, 0, 0};
    int decode;
    cout << "input string: ";
    cin.get(tweet, 280);
    string str(tweet);
    string news = enigmaEncode(str, pluh, rotors, intialNum);
    cout << news << "\n";
    cout << "decode? ";
    cin >> decode;
    if (decode) {cout << enigmaDecode(news, pluh, rotors, intialNum) << "\n";}
    return 0;
}