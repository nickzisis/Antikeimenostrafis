#ifndef VERTEX_HPP 
#define VERTEX_HPP

#include "Edges.hpp"
#include <list>

class Vertex {
    private:
        unsigned long int id;
        double longitude;
        double latitude;
        std::list<Edges> edges; 
    public:
        Vertex(unsigned long int id, double longitude, double latitude);
        Vertex(const Vertex& other);
        unsigned long int GetId() const;
        double GetLongitude() const;
        double GetLatitude() const;
        void AddEdge(Edges edge);
        std::list<Edges> GetEdges() const;
        void RemoveEdge(unsigned long int endId);
};
#endif