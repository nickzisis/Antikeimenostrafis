#include <iostream>
#include <string>
#include <sstream>
#include "Graph.hpp"
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
    string filepath;
    Graph graph;
    unsigned long int startId = 0, endId = 0;

    while (true) {
        printMenu();
        getline(cin, input); 
        
        if ((input.empty()) || (correctInputs.find(input[0]) == string::npos)) {
            cout << "Wrong Input. Expected format i/c/p/b/d/q." << endl;
            continue;
        }
        
        char command = input[0];
        input[0] = ' '; 
        stringstream ss(input);

        switch (command) {
            case 'q':
                return 0;
            case 'c':
                break;
            case 'p': {
                
                if (!(ss >> startId >> endId)) {
                    cout << "Wrong Input. Expected format: p <startId> <endId>" << endl;
                    break;
                }
                
                if (graph.isEmpty()) {
                    cout << "Graph is empty. Load the graph first." << endl;
                    break;
                }

                list<unsigned long int> shortestPath;
                shortestPath = graph.dijkstra(startId, endId);

                break;
            }
            case 'b':
                
                if (!(ss >> startId)) {
                    cout << "Wrong Input. Expected format: b <startId>" << endl;
                    break;
                }
                break;
            case 'd':
                
                if (!(ss >> startId)) {
                    cout << "Wrong Input. Expected format: d <startId>" << endl;
                    break;
                }

                break;
            case 'i':
                if (!(ss >> filepath)) {
                    cout << "Wrong Input. Expected format: i <filepath>" << endl;
                    break;
                }

                graph = Graph(input.substr(1).c_str());
                break;
            default:
                break;
                
        }
    }

    return 0;
}