#include "Edges.hpp"

Edges::Edges (unsigned long int startId, unsigned long int endId, double distance) {
    this->startId = startId;
    this->endId = endId;
    this->distance = distance;
}

Edges::Edges (const Edges& other) {
    this->startId = other.startId;
    this->endId = other.endId;
    this->distance = other.distance;
}

unsigned long int Edges::GetStartId() {
    return this->startId;
}

unsigned long int Edges::GetEndId() {
    return this->endId;
}

double Edges::GetDistance() {
    return this->distance;
}

void Edges::SetStartId(unsigned long int startId) {
    this->startId = startId;
}

void Edges::SetEndId(unsigned long int endId) {
    this->endId = endId;
}