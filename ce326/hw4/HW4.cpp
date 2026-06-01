#include <iostream>
#include <string>
#include "Graph.hpp"
using namespace std;

void printMenu() {
    //cout << endl << "-i <filepath>  :  Import Graph from <filepath>" << endl;
    //cout << "-c             :  Compact Graph" << endl;
    //cout << "-p <sid> <eid> :  Estimate the shortest path between start node with <sid> and end node with <eid>" << endl;
    //cout << "-b <sid>       :  Print bfs starting from node with <sid>" << endl;
    //cout << "-d <sid>       :  Print dfs starting from node with <sid>" << endl;
    //cout << "-q             :  Exit without memory leaks" << endl;
    //cout << endl;
    cout << endl << "Enter your choice: " << endl;
}

int main() {

    string input;
    string correctInputs = "icpbdq";
    string filepath;
    Graph* graph = nullptr;
    list<unsigned long int> shortestPath, bfsResult, dfsResult;
    unsigned long int startId = 0, endId = 0;

    while (true) {
        printMenu();
        getline(cin, input);

        if (input.empty() || input[0] != '-' || input.size() < 2 || correctInputs.find(input[1]) == string::npos) {
            cout << "Wrong Input. Expected format -i/-c/-p/-b/-d/-q." << endl;
            continue;
        }

        char command = input[1];
        input[0] = ' ';
        input[1] = ' ';
        stringstream ss(input);

        switch (command) {
            case 'q':
                delete graph;
                return 0;
            case 'c':
                if (graph) {
                    graph->compactGraph();
                    cout << "Compact OK" << endl;
                }
                break;
            case 'p': {
                
                if (!(ss >> startId >> endId)) {
                    cout << "Wrong Input. Expected format: p <startId> <endId>" << endl;
                    break;
                }
                
                if (graph->isEmpty()) {
                    cout << "Graph is empty. Load the graph first." << endl;
                    break;
                }

                shortestPath = graph->dijkstra(startId, endId);
                graph->printDijkstraPath(shortestPath);
                break;
            }
            case 'b':
                
                if (!(ss >> startId)) {
                    cout << "Wrong Input. Expected format: b <startId>" << endl;
                    break;
                }

                bfsResult = graph->BFS(startId);
                for (const auto& id : bfsResult) {
                    cout << id << endl;
                }

                break;
            case 'd':
                
                if (!(ss >> startId)) {
                    cout << "Wrong Input. Expected format: d <startId>" << endl;
                    break;
                }
                
                dfsResult = graph->DFS(startId);
                for (const auto& id : dfsResult) {
                    cout << id << endl;
                }

                break;
            case 'i':
                if (!(ss >> filepath)) {
                    cout << "Wrong Input. Expected format: i <filepath>" << endl;
                    break;
                }
                delete graph;                
                graph = new Graph(filepath.c_str());
                break;
            default:
                break;
                
        }
    }

    return 0;
}