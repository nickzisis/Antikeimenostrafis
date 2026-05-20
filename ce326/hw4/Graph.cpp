#include "Graph.hpp"

Graph::Graph() {

}

//Calculates the harvesine distance.
static double harvesine(double lat1, double lon1, double lat2, double lon2) {
    double result, a, c, R, deltaLat, deltaLon, rad;

    rad = M_PI / 180;
    R = 6378137;
    deltaLat = lat2 - lat1;
    deltaLon = lon2 - lon1;

    a = pow(sin((deltaLat * rad) /2),2) + cos(lat1 * rad) * cos(lat2 * rad) * pow(((deltaLon * rad)/2),2);
    c = 2 * atan2(sqrt(a),sqrt(1-a));
    result = R * c;

    return result;
}

//Calculates the factor of each way.
static double factorCalc(const char* v) {
    double factor;

    if (strcmp(v, "motorway") == 0 || strcmp(v, "trunk") == 0) {
        factor = 0.5;
    } 
    else if (strcmp(v, "primary") == 0 || strcmp(v, "secondary") == 0) {
        factor = 0.75;
    }
    else if (strcmp(v, "residential") == 0 || strcmp(v, "tertiary") == 0) {
        factor = 1;
    }
    else if (strcmp(v, "living_street") == 0 || strcmp(v, "unclassified") == 0) {
        factor = 1.25;
    }
    else if (strcmp(v, "service") == 0 || strcmp(v, "track") == 0) {
        factor = 1.5;
    }

    return factor;
}

//Reads for the file then adds the edges to the graph.
void Graph::addWays (XMLNode* pRoot) {
    XMLElement* pWay = pRoot->FirstChildElement("way");
    if (pWay == nullptr) {
        cout << "Error: Invalid XML file structure." << endl;
        return;
    }

    double factor;
    const char* highway_type;

    while(pWay != nullptr) {
        bool oneway = false, is_highway = false;

        XMLElement* tag = pWay->FirstChildElement("tag");
        if (tag == nullptr) {
            pWay = pWay->NextSiblingElement("way");
            continue;
        }
       
        while (tag != nullptr) {;
            const char * k = tag->Attribute("k");
            const char * v = tag->Attribute("v");


            if (strcmp(k, "highway") == 0) {
                if (strcmp(v, "residential") == 0 || strcmp(v, "primary") == 0 || strcmp(v, "secondary") == 0 || strcmp(v, "tertiary") == 0
                    || strcmp(v, "trunk") == 0 || strcmp(v, "motorway") == 0 || strcmp(v, "living_street") == 0 || strcmp(v, "unclassified") == 0
                    || strcmp(v, "service") == 0 || strcmp(v, "track") == 0) {
                        is_highway = true;
                        highway_type = v;
                }
            }

            if (is_highway) {
                if (strcmp(k, "oneway") == 0) {
                    if (strcmp(v, "yes") == 0) {
                        oneway = true;
                    }
                    else {
                        oneway = false;
                    }
                } 
            }

            tag = tag->NextSiblingElement("tag");
        }
        
        if (is_highway) {
            unsigned long int id1, id2;
            double distance;

            XMLElement* nd1 = pWay->FirstChildElement("nd");
            if (nd1 == nullptr) {
                pWay = pWay->NextSiblingElement("way");
                continue;
            }
            nd1->QueryAttribute("ref", &id1);

            XMLElement* nd2 = nd1->NextSiblingElement("nd");
            if (nd2 == nullptr) {
                pWay = pWay->NextSiblingElement("way");
                continue;
            }
            nd2->QueryAttribute("ref", &id2);
            
            factor = factorCalc(highway_type);
            distance = factor * harvesine(vertices[vertex_id[id1]].GetLatitude(), vertices[vertex_id[id1]].GetLongitude(), vertices[vertex_id[id2]].GetLatitude(), vertices[vertex_id[id2]].GetLongitude());
            AddEdge(id1, id2, distance, oneway);
            
            nd1 = nd2;
            nd2 = nd2->NextSiblingElement("nd");

            while(nd2 != nullptr) {
                nd1->QueryAttribute("ref", &id1);
                nd2->QueryAttribute("ref", &id2);

                factor = factorCalc(highway_type);
                distance = factor * harvesine(vertices[vertex_id[id1]].GetLatitude(), vertices[vertex_id[id1]].GetLongitude(), vertices[vertex_id[id2]].GetLatitude(), vertices[vertex_id[id2]].GetLongitude());
                AddEdge(id1, id2, distance, oneway);
            
                nd1 = nd2;
                nd2 = nd2->NextSiblingElement("nd");
            }
        }
        
        pWay = pWay->NextSiblingElement("way");
    }
}

//Reads from the file then adds the nodes to the graph.
void Graph::addNodes (XMLNode* pRoot) {
    XMLElement* pVertex = pRoot->FirstChildElement("node");
        if (pVertex == nullptr) {
        cout << "Error: Invalid XML file structure." << endl;
        return;
    }

    while (pVertex !=  nullptr) {
        double longitude, latitude;
        unsigned long int id;

        pVertex->QueryAttribute("id", &id);
        pVertex->QueryDoubleAttribute("lat", &latitude);
        pVertex->QueryDoubleAttribute("lon", &longitude);

        AddVertex(Vertex(id, longitude, latitude));
        
        pVertex = pVertex->NextSiblingElement("node");
    }
}

//Removes the empty vertices from the graph.
void Graph::removeVertices() {
    unordered_set<unsigned long int> endIds;

    for (const auto& vertex : vertices) {
        for (const auto& edge : vertex.GetEdges()) {
            endIds.insert(edge.GetEndId());
        }
    }


    for (int i = vertices.size() - 1; i >= 0 ; --i ) {
        if ((vertices[i].GetEdges().empty()) && (endIds.find(vertices[i].GetId()) == endIds.end())) {
            removeVertex(vertices[i].GetId());
        }
    }
}

//Creates the graph.
Graph::Graph(string filename) {
    XMLDocument doc;
    XMLError error =  doc.LoadFile(filename.c_str());
    
    if (error != XML_SUCCESS) {
        cout << "Error loading XML file: " << doc.ErrorStr() << endl;
        return;
    }

    XMLNode* pRoot = doc.FirstChildElement("osm");
    if (pRoot == nullptr) {
        cout << "Error: Invalid XML file structure." << endl;
        return;
    } 

    addNodes(pRoot);
    addWays(pRoot);
    removeVertices();
}

//Adds a vertex to the graph.
void Graph::AddVertex(Vertex vertex) {
    unsigned long int id = vertex.GetId();

    vertices.push_back(vertex);
    vertex_id[id] = vertices.size() - 1;
}

//Adds an edge to the graph.
void Graph::AddEdge(unsigned long int id1, unsigned long int id2, double distance, bool oneway) {
    if ((vertex_id.find(id1) != vertex_id.end()) && (vertex_id.find(id2) != vertex_id.end())) {
        unsigned int index1 = vertex_id[id1];
        unsigned int index2 = vertex_id[id2];

        Edges edge(id1, id2, distance, oneway);
        vertices[index1].AddEdge(edge);
        if (!oneway) {
            Edges reverse_edge(id2, id1, distance, oneway);
            vertices[index2].AddEdge(reverse_edge);
        }
    }
}

//Removes a vertex and its edges from the graph.
void Graph::removeVertex(unsigned long int id) {
    unsigned int deleted_index = vertex_id[id];

    for (auto& vertex : vertices) {
        if (vertex.GetId() != id) {
            vertex.RemoveEdge(id);
        }
    }

    vertices.erase(vertices.begin() + deleted_index);
    vertex_id.erase(id);

    for (auto& pair : vertex_id) {
        if (pair.second > deleted_index) {
            pair.second--;
        }
    }
}

//Removes an edge from the graph, and itself from every vertex it was in.
void Graph::removeEdge(unsigned long int id1, unsigned long int id2) {
    if ((vertex_id.find(id1) != vertex_id.end()) && (vertex_id.find(id2) != vertex_id.end())) {
        unsigned int index1 = vertex_id[id1];
        unsigned int index2 = vertex_id[id2];

        vertices[index1].RemoveEdge(id2);
        vertices[index2].RemoveEdge(id1);
    }
}

//Returns the adjacent vertices from a specified vertex.
vector<unsigned long int> Graph::getAdjacentVertices(unsigned long int id) {
    vector<unsigned long int> adjacentVertices;
    
    if (vertex_id.find(id) != vertex_id.end()) {
        unsigned int index = vertex_id[id];
        
        for (const auto& edge : vertices[index].GetEdges()) {
            adjacentVertices.push_back(edge.GetEndId());
        }
    }
    return adjacentVertices;
}

//Shortest path dijkstra algorithm.
list<unsigned long int> Graph::dijkstra(unsigned long int startId, unsigned long endId) {
    unordered_map<unsigned long int, double> dist;
    unordered_map<unsigned long int, unsigned long int> prev;
    set<pair<double, unsigned long int>> pq;
    list<unsigned long int> endPath;

    for (const auto& vertex : vertices) {
        dist[vertex.GetId()] = numeric_limits<double>::infinity();
    }

    dist[startId] = 0.0;
    pq.insert({0.0, startId});


    while(!pq.empty()) {
        auto it = pq.begin();
        pair<double, unsigned long int> current = *it;
        pq.erase(it);

        unsigned long int currentId = current.second;
        double currentDist = current.first;

        if (currentId == endId) {
            break;
        }

        for (const auto& neighbor : vertices[vertex_id[currentId]].GetEdges()) {
            unsigned long int neighborId = neighbor.GetEndId();
            double newDist = currentDist + neighbor.GetDistance();

            if (newDist < dist[neighborId]) {

                prev[neighborId] = currentId;
                dist[neighborId] = newDist;
                pq.insert({newDist,neighborId});
            }
        }
    }   

    if (prev.find(endId) == prev.end() && endId != startId) {
        return list<unsigned long>();
    }

    unsigned long int id = endId;
    while (id != startId) {
        endPath.push_front(id);
        id = prev[id];
    }
    endPath.push_front(startId);

    return endPath;
}

//Checks if the graph is empty.
bool Graph::isEmpty() {
    bool isEmpty = true;
    
    if (!(vertices.empty())) {
        isEmpty = false;
    }

    return isEmpty;
}