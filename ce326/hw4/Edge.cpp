#include "Edges.hpp"

Edges::Edges (unsigned long int startId, unsigned long int endId, double distance, bool oneway) {
    this->startId = startId;
    this->endId = endId;
    this->distance = distance;
    this->oneway = oneway;
}

Edges::Edges (const Edges& other) {
    this->startId = other.startId;
    this->endId = other.endId;
    this->distance = other.distance;
    this->oneway = other.oneway;
}

unsigned long int Edges::GetStartId() const {
    return this->startId;
}

unsigned long int Edges::GetEndId() const {
    return this->endId;
}

double Edges::GetDistance() const {
    return this->distance;
}

bool Edges::GetOneway() const {
    return this->oneway;
}

void Edges::SetStartId(unsigned long int startId) {
    this->startId = startId;
}

void Edges::SetEndId(unsigned long int endId) {
    this->endId = endId;
}