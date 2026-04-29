#include <iostream>
using namespace std;
#include <regex>
#include <string>

void parseInput(string input) {
    regex variableRegex(R"(^([a-zA-Z_][a-zA-Z0-9_]*))");
    regex variableAssignmentRegex(R"(^([a-zA-Z_][a-zA-Z0-9_]*)\s*=)");
    regex numberRegex(R"(^([0-9]+))");
    regex doubleRegex(R"(^(-?[0-9]+\.[0-9]+))");
    regex stringRegex(R"(^\"([^\"]*)\"|^'([^']*)')");

    regex whitespaceRegex(R"(^\s+)"); 

    smatch matches;

    while (!input.empty()) {
        
        if (regex_search(input, matches, whitespaceRegex)) {
            input = matches.suffix().str(); 
            // suffix().str() means "give me the rest of the string after the match"
        }
        else if (regex_search(input, matches, variableAssignmentRegex)) {
            cout << "Found variable assignment: " << matches[1] << endl;
            input = matches.suffix().str();
        } 
        else if (regex_search(input, matches, variableRegex)) {
            cout << "Found variable: " << matches[1] << endl;
            input = matches.suffix().str();
        }
        else if (regex_search(input, matches, doubleRegex)) {
            cout << "Found a double number: " << matches[1] << endl;
            input = matches.suffix().str();
        }
        else if (regex_search(input, matches, numberRegex)) {
            cout << "Found an integer number: " << matches[1] << endl;
            input = matches.suffix().str();
        }
        else if (regex_search(input, matches, stringRegex)) {
            string foundStr = matches[1].matched ? matches[1] : matches[2];
            cout << "Found a string: " << foundStr << endl;
            input = matches.suffix().str();
        }
        else {
            cout << "Error: Unrecognized symbol at '" << input << "'" << endl;
            break;
        }
    }
}

int main() {

    string test;

    cout << "Enter a test string: " << endl;
    
    getline(cin, test);

    cout << "You entered: " << test << endl;
    parseInput(test);

    return 0;
}