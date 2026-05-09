#include <iostream>
#include <string>
#include "Parser.hpp"
using namespace std;
 

int main() {
    string line;
    while (getline(cin, line)) {
        parseLine(line);
    }
    return 0;
}
 