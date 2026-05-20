#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Vertex.hpp"

#include "tinyxml2.h"
using namespace tinyxml2;
#include <iostream>
using namespace std;

#include <string>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>

class Graph {
    private:
        vector<Vertex> vertices;
        unordered_map<unsigned long , unsigned int> vertex_id;

        void addNodes(XMLNode* pRoot);
        void addWays(XMLNode* pRoot);
        void removeVertices();
    public:
        Graph(string filename);
        Graph();
        void AddVertex(Vertex vertex);
        void AddEdge(unsigned long int id1, unsigned long int id2, double distance, bool oneway);
        void removeVertex(unsigned long int id);
        void removeEdge(unsigned long int id1, unsigned long int id2);
        vector<unsigned long int> getAdjacentVertices(unsigned long int id);
        
        bool isEmpty();
        list<unsigned long int> dijkstra(unsigned long int startId, unsigned long endId);
    };

#endif