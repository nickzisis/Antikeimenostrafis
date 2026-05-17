#ifndef EDGES_HPP
#define EDGES_HPP

class Edges {
    private:
        unsigned long int startId;
        unsigned long int endId;
        double distance;
        bool oneway;
    public:
        Edges(unsigned long int startId, unsigned long int endId, double distance, bool oneway);
        Edges (const Edges& other);
        unsigned long int GetStartId() const;
        unsigned long int GetEndId() const;
        double GetDistance() const;
        bool GetOneway() const;
        void SetStartId(unsigned long int startId);
        void SetEndId(unsigned long int endId);
};

#endif