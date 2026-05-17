#include "Graph.hpp"

static double harvesine(double lat1, double lon1, double lat2, double lon2) {
    double result, a, c, R, deltaLat, deltaLon, rad;

    rad = M_PI / 180;
    R = 6378137;
    deltaLat = lat2 - lat1;
    deltaLon = lon2 - lon1;

    a = pow(((deltaLat * rad) /2),2) + cos(lat1 * rad) * cos(lat2 * rad) * pow(((deltaLon * rad)/2),2);
    c = 2 * atan2(sqrt(a),sqrt(1-a));
    result = R * c;

    return result;
}

void Graph::addWays (XMLNode* pRoot) {
        XMLElement* pWay = pRoot->FirstChildElement("way");
    if (pWay == nullptr) {
        cout << "Error: Invalid XML file structure." << endl;
        return;
    }

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

            distance = harvesine(vertices[vertex_id[id1]].GetLatitude(), vertices[vertex_id[id1]].GetLongitude(), vertices[vertex_id[id2]].GetLatitude(), vertices[vertex_id[id2]].GetLongitude());
            AddEdge(id1, id2, 0.0, oneway);
            
            nd1 = nd2;
            nd2 = nd2->NextSiblingElement("nd");

            while(nd2 != nullptr) {
                nd1->QueryAttribute("ref", &id1);
                nd2->QueryAttribute("ref", &id2);

                distance = harvesine(vertices[vertex_id[id1]].GetLatitude(), vertices[vertex_id[id1]].GetLongitude(), vertices[vertex_id[id2]].GetLatitude(), vertices[vertex_id[id2]].GetLongitude());
                AddEdge(id1, id2, distance, oneway);
            
                nd1 = nd2;
                nd2 = nd2->NextSiblingElement("nd");
            }
        }
        
        pWay = pWay->NextSiblingElement("way");
    }
}

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

void Graph::removeVertices() {
    for (int i = vertices.size() - 1; i == 0 ; --i ) {
        if (vertices[i].GetEdges().empty()) {
            removeVertex(vertices[i].GetId());
        }
    }
}

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
}

void Graph::AddVertex(Vertex vertex) {
    unsigned long int id = vertex.GetId();

    vertices.push_back(vertex);
    vertex_id[id] = vertices.size() - 1;
}

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

void Graph::removeEdge(unsigned long int id1, unsigned long int id2) {
    if ((vertex_id.find(id1) != vertex_id.end()) && (vertex_id.find(id2) != vertex_id.end())) {
        unsigned int index1 = vertex_id[id1];
        unsigned int index2 = vertex_id[id2];

        vertices[index1].RemoveEdge(id2);
        vertices[index2].RemoveEdge(id1);
    }
}

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