#ifndef EDGES_HPP
#define EDGES_HPP

class Edges {
    private:
        unsigned long int startId;
        unsigned long int endId;
        double distance;
    public:
        Edges(unsigned long int startId, unsigned long int endId, double distance);
        Edges (const Edges& other);
        unsigned long int GetStartId();
        unsigned long int GetEndId();
        double GetDistance();
        void SetStartId(unsigned long int startId);
        void SetEndId(unsigned long int endId);
};

#endif