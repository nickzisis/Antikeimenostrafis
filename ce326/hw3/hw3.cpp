#include <iostream>
#include <string>
#include "Parser.hpp"
using namespace std;
 

int main() {
    Parser parse;
    string line;

    cout << "$> " << endl;
    while (getline(cin, line)) {    
        parse.parseLine(line);
        cout << "$> " << endl;
    }  
    return 0;
}
 