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

class Graph {
    private:
        std::vector<Vertex> vertices;
        std::unordered_map<unsigned long , unsigned int> vertex_id;

        void addNodes(XMLNode* pRoot);
        void addWays(XMLNode* pRoot);
        void removeVertices();
    public:
        Graph(std::string filename);
        void AddVertex(Vertex vertex);
        void AddEdge(unsigned long int id1, unsigned long int id2, double distance, bool oneway);
        void removeVertex(unsigned long int id);
        void removeEdge(unsigned long int id1, unsigned long int id2);
        std::vector<unsigned long int> getAdjacentVertices(unsigned long int id);
};

#endif