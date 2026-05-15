#include <iostream>
#include <string>

using namespace std;

void printMenu() {
    cout << endl << "-i <filepath>  :  Import Graph from <filepath>" << endl;
    cout << "-c             :  Compact Graph" << endl;
    cout << "-p <sid> <eid> :  Estimate the shortest path between start node with <sid> and end node with <eid>" << endl;
    cout << "-b <sid>       :  Print bfs starting from node with <sid>" << endl;
    cout << "-d <sid>       :  Print dfs starting from node with <sid>" << endl;
    cout << "-q             :  Exit without memory leaks" << endl;
    cout << endl;
    cout << "Enter your choice: " << endl;
}

int main() {

    string input;
    string correctInputs = "icpbdq";
    
    while (true) {
        printMenu();
        getline(cin, input); 
        
        if ((input.length() != 1) || (correctInputs.find(input) == string::npos)) {
            cout << "Wrong Input" << endl;
            continue;
        }
        else {
            switch (input[0]) {
                case 'q':
                    return 0;
                case 'c':
                    break;
                case 'p':
                    break;
                case 'b':
                    break;
                case 'd':
                    break;
                case 'i':
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}