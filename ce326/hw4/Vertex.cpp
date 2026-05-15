#include "Vertex.hpp"

Vertex::Vertex(unsigned long int id, double longitude, double latitude) {
    this->id = id;
    this->longitude = longitude;
    this->latitude = latitude;
}

Vertex::Vertex(const Vertex& other) {
    this->id = other.id;
    this->longitude = other.longitude;
    this->latitude = other.latitude;
}

unsigned long int Vertex::GetId() {
    return this->id;
}

double Vertex::GetLongitude() {
    return this->longitude;
}

double Vertex::GetLatitude() {
    return this->latitude;
}