#include "Vertex.hpp"

Vertex::Vertex(unsigned long int id, double longitude, double latitude) {
    this->id = id;
    this->longitude = longitude;
    this->latitude = latitude;
    this->edges = std::list<Edges>();
}

Vertex::Vertex(const Vertex& other) {
    this->id = other.id;
    this->longitude = other.longitude;
    this->latitude = other.latitude;
    this->edges = other.edges;
}

unsigned long int Vertex::GetId() const {
    return this->id;
}

double Vertex::GetLongitude() const {
    return this->longitude;
}

double Vertex::GetLatitude() const {
    return this->latitude;
}

void Vertex::AddEdge(Edges edge) {
    this->edges.push_back(edge);
}

std::list<Edges> Vertex::GetEdges() const {
    return this->edges;
}

void Vertex::RemoveEdge(unsigned long int endId) {
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (it->GetEndId() == endId) {
            edges.erase(it);
            break;
        }
    }
}