#ifndef VERTEX_HPP 
#define VERTEX_HPP

#include "Edges.hpp"
#include <list>
class Vertex {
    private:
        unsigned long int id;
        double longitude;
        double latitude;
    public:
        Vertex(unsigned long int id, double longitude, double latitude);
        Vertex(const Vertex& other);
        unsigned long int GetId();
        double GetLongitude();
        double GetLatitude();
};
#endif