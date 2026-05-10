#include <iostream>
#include <string>
#include "Parser.hpp"
using namespace std;
 

int main() {
    Parser parse;
    string line;

    while (getline(cin, line)) {
        parse.parseLine(line);
    }
    return 0;
}
 