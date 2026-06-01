#include "Graph.hpp"

//Default constructor
Graph::Graph() {

}

//Calculates the harvesine distance.
static double harvesine(double lat1, double lon1, double lat2, double lon2) {
    double result; 
    double a, c, R, deltaLat, deltaLon, rad;
    double two = 2;
    double one = 1;

    rad = M_PI / 180;
    R = 6378137;
    deltaLat = lat2 - lat1;
    deltaLon = lon2 - lon1;

    a = pow(sin((deltaLat * rad) /two),two) + cos(lat1 * rad) * cos(lat2 * rad) * pow(sin((deltaLon * rad)/two),two);
    c = two * atan2(sqrt(a),sqrt(one-a));
    result = R * c;

    return result;
}

//Calculates the factor of each way.
static double factorCalc(const char* v) {
    double factor = 1;

    if (v == nullptr) return factor;

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

//Adds the nodes to the graph, by reading the XML file.
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

//Adds the ways to the graph, by reading the XML file.
void Graph::addWays (XMLNode* pRoot) {
    XMLElement* pWay = pRoot->FirstChildElement("way");
    if (pWay == nullptr) {
        cout << "Error: Invalid XML file structure." << endl;
        return;
    }

    double factor;
    const char* highway_type;

    while(pWay != nullptr) {
        bool oneway = false, is_highway = false, reverse_oneway = false, has_explicit_oneway = false;
        highway_type = nullptr;

        XMLElement* tag = pWay->FirstChildElement("tag");
        if (tag == nullptr) {
            pWay = pWay->NextSiblingElement("way");
            continue;
        }
       
        while (tag != nullptr) {
            const char * k = tag->Attribute("k");
            const char * v = tag->Attribute("v");

            if (k && v) {
                if (strcmp(k, "highway") == 0) {
                    is_highway = true;
                    highway_type = v;
                }

                if (strcmp(k, "oneway") == 0) {
                    has_explicit_oneway = true;
                    if (strcmp(v, "yes") == 0 || strcmp(v, "1") == 0) {
                        oneway = true;
                        reverse_oneway = false;
                    }
                    else if(strcmp(v, "-1") == 0){
                        oneway = true;
                        reverse_oneway = true;
                    }
                    else {
                        oneway = false;
                        reverse_oneway = false;
                    }
                } 
            }
            tag = tag->NextSiblingElement("tag");
        }

        if (is_highway && !has_explicit_oneway && highway_type != nullptr) {
            if (strcmp(highway_type, "motorway") == 0 || 
                strcmp(highway_type, "motorway_link") == 0 ||
                strcmp(highway_type, "trunk") == 0 || 
                strcmp(highway_type, "trunk_link") == 0) {
                
                oneway = true;
            }
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
            
            //Check if both nodes exist in the graph before calculating the distance and adding the edge
            if (vertex_id.find(id1) != vertex_id.end() && vertex_id.find(id2) != vertex_id.end()) {
                factor = factorCalc(highway_type);
                distance = factor * harvesine(vertices[vertex_id.at(id1)].GetLatitude(), vertices[vertex_id.at(id1)].GetLongitude(), vertices[vertex_id.at(id2)].GetLatitude(), vertices[vertex_id.at(id2)].GetLongitude());
                if (reverse_oneway){
                    AddEdge(id2, id1, distance, true);
                } else {
                    AddEdge(id1, id2, distance, oneway);
                }
            }
            
        
            nd1 = nd2;
            nd2 = nd2->NextSiblingElement("nd");

            while(nd2 != nullptr) {
                nd1->QueryAttribute("ref", &id1);
                nd2->QueryAttribute("ref", &id2);

                //does the same thing here as above
                if (vertex_id.find(id1) != vertex_id.end() && vertex_id.find(id2) != vertex_id.end()) {
                    factor = factorCalc(highway_type);
                    distance = factor * harvesine(vertices[vertex_id.at(id1)].GetLatitude(), vertices[vertex_id.at(id1)].GetLongitude(), vertices[vertex_id.at(id2)].GetLatitude(), vertices[vertex_id.at(id2)].GetLongitude());
                    if (reverse_oneway){
                        AddEdge(id2, id1, distance, true);
                    } else {
                        AddEdge(id1, id2, distance, oneway);
                    }
                }
                
            
                nd1 = nd2;
                nd2 = nd2->NextSiblingElement("nd");
            }
        }
        pWay = pWay->NextSiblingElement("way");
    }

    //Removes any vertices that are not connected to any edge, as they are not useful for the graph.
    unordered_set<unsigned long int> connectedNodes;
    for (const auto& vertex : vertices) {
        if (!vertex.GetEdges().empty()) {
            connectedNodes.insert(vertex.GetId());
            for (const auto& edge : vertex.GetEdges()) {
                connectedNodes.insert(edge.GetEndId());
            }
        }
    }
    
    for (int i = vertices.size() - 1; i >= 0; --i) {
        if (connectedNodes.find(vertices[i].GetId()) == connectedNodes.end()) {
            removeVertex(vertices[i].GetId());
        }
    }
}

//Creates the graph.
Graph::Graph(string filename) {
    if (filename.size() >= 4 && filename.substr(filename.size() - 4) == ".txt") {
        cout << "Invalid format for file: " << filename << endl;
        return;
    }

    XMLDocument doc;
    XMLError error =  doc.LoadFile(filename.c_str());
    
    if (error != XML_SUCCESS) {
        cout << "Unable to open file: " << filename << endl;
        return;
    }

    XMLNode* pRoot = doc.FirstChildElement("osm");
    if (pRoot == nullptr) {
        cout << "Error: Invalid XML file structure." << endl;
        return;
    } 

    addNodes(pRoot);
    addWays(pRoot);
    cout << "Graph OK" << endl;
}

//Adds a vertex to the graph.
void Graph::AddVertex(Vertex vertex) {
    unsigned long int id = vertex.GetId();

    vertices.push_back(vertex);
    vertex_id[id] = vertices.size() - 1;
}

//Adds an edge to the graph.
void Graph::AddEdge(unsigned long int id1, unsigned long int id2, double distance, bool oneway) {
    if (vertex_id.find(id1) == vertex_id.end() || vertex_id.find(id2) == vertex_id.end())
        return;

    unsigned int index1 = vertex_id[id1];
    unsigned int index2 = vertex_id[id2];

    //Cheks for existing edge in the forward direction (id1 -> id2) and updates it if the new distance is smaller
    bool should_add_forward = true;
    for (const auto& e : vertices[index1].GetEdges()) {
        if (e.GetEndId() == id2) {
            if (distance < e.GetDistance()) {
                vertices[index1].RemoveEdge(id2);
            } else {
                should_add_forward = false;
            }
            break;
        }
    }

    if (should_add_forward) {
        Edges edge(id1, id2, distance, oneway);
        vertices[index1].AddEdge(edge);
    }

    // does the same thing here for the backward direction
    if (!oneway) {
        bool should_add_backward = true;
        for (const auto& e : vertices[index2].GetEdges()) {
            if (e.GetEndId() == id1) {
                if (distance < e.GetDistance()) {
                    vertices[index2].RemoveEdge(id1);
                } else {
                    should_add_backward = false;
                }
                break;
            }
        }
        
        if (should_add_backward) {
            Edges reverse_edge(id2, id1, distance, oneway);
            vertices[index2].AddEdge(reverse_edge);
        }
    }
}

//Removes a vertex and its edges from the graph.
void Graph::removeVertex(unsigned long int id) {
    if (vertex_id.find(id) == vertex_id.end()) return;
    
    for (auto& vertex : vertices) {
        vertex.RemoveEdge(id);
    }

    unsigned int index = vertex_id[id];
    vertices.erase(vertices.begin() + index);
    vertex_id.erase(id);
    
    for (auto& pair : vertex_id) {
        if (pair.second > index) {
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

    if (vertex_id.find(startId) == vertex_id.end() || vertex_id.find(endId) == vertex_id.end()) {
        return list<unsigned long int>();
    }

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

        if (currentDist > dist[currentId]) {
            continue;
        }

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

//Prints the path of the dijkstra algorithm, with the distance of each edge and a google maps link.
void Graph::printDijkstraPath(list<unsigned long int> path) {
    if (path.empty()) {
        return; 
    }

    auto it = path.begin();
    auto next = it;
    next++;

    double totalDistance = 0.0; 

    while (next != path.end()) {
        for (const auto& edge : vertices[vertex_id[*it]].GetEdges()) {
            if (edge.GetEndId() == *next) {
                totalDistance += edge.GetDistance(); 
                
                cout << "[" << *it << " -> " << *next << "] ";
                cout << fixed << setprecision(3) << totalDistance << endl; 
                break;
            }
        }
        it = next;
        next++;
    }

    cout << endl;

    cout << "https://www.google.com/maps/dir/";
    for (const auto& id : path) {
        unsigned int index = vertex_id[id];
        
        //if 4th digit is 0, print 3 digits by removing the 4th digit
        stringstream ssLat;
        ssLat << fixed << setprecision(4) << vertices[index].GetLatitude();
        string latStr = ssLat.str();
        for (int i=0; i < (int)latStr.size() ; i++) {
            if (latStr.back() == '0') {
                latStr.pop_back(); 
            }
        }

        //same thing here
        stringstream ssLon;
        ssLon << fixed << setprecision(4) << vertices[index].GetLongitude();
        string lonStr = ssLon.str();
        for (int i = 0 ; i < (int)lonStr.size() ; i++ ) {
            if (lonStr.back() == '0') {
                lonStr.pop_back(); 
            }
        }    
        
        cout << latStr << "," << lonStr << "/";
    }
    cout << endl;
}

//Checks if the graph is empty.
bool Graph::isEmpty() {
    bool isEmpty = true;
    
    if (!(vertices.empty())) {
        isEmpty = false;
    }

    return isEmpty;
}

//Does the bfs traversal for the graph, starting from a specified vertex.
list<unsigned long int> Graph::BFS(unsigned long int id) {
    list<unsigned long int> result;
    unordered_set<unsigned long int> visited;
    queue<unsigned long int> q;

    if (vertex_id.find(id) == vertex_id.end()) {
        return result; 
    }

    q.push(id);
    visited.insert(id);

    while(!(q.empty())) {
        unsigned long int current = q.front();
        q.pop();
        result.push_back(current);

        set<unsigned long int> neighbors;
        for (const auto& edge : vertices[vertex_id[current]].GetEdges()) {
            neighbors.insert(edge.GetEndId());
        }
        
        for (const auto& i : neighbors) {
            if(visited.find(i) == visited.end()) {
                visited.insert(i);
                q.push(i);
                

            }
        }
    }

    return result;
}

//Does the dfs traversal for the graph, starting from a specified vertex.
list<unsigned long int> Graph::DFS(unsigned long int id) {
    list<unsigned long int> result;
    unordered_set<unsigned long int> visited;
    stack<unsigned long int> q;

    if (vertex_id.find(id) == vertex_id.end()) {
        return result; 
    }

    q.push(id);

    while(!(q.empty())) {
        unsigned long int current = q.top();
        q.pop();
        
        if (visited.find(current) == visited.end()) {
            visited.insert(current);
            result.push_back(current);
            
            set<unsigned long int> neighbors;
            for (const auto& edge : vertices[vertex_id[current]].GetEdges()) {
                neighbors.insert(edge.GetEndId());
            }

            for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
                if (visited.find(*it) == visited.end()) {
                    q.push(*it); 
                }
            }
        }
    }

    return result;
}

// Compacts the graph by removing vertices that have only one incoming and one outgoing edge,
//  and updating the distances of the remaining edges accordingly.
void Graph::compactGraph() {
    bool changed = true;

    while (changed) {
        changed = false;
        unordered_map<unsigned long, vector<pair<unsigned long, Edges>>> inMap;
        for (const auto& v : vertices) {
            for (const auto& e : v.GetEdges()) {
                inMap[e.GetEndId()].emplace_back(v.GetId(), e);
            }
        }

        vector<unsigned long> eSrc, eDst;
        vector<double>        eDist;
        vector<bool>          eOneway;
        vector<unsigned long> toRemove;
        unordered_set<unsigned long> marked; 
        
        //Goes through the graph and checks for vertices that have only one incoming and one outgoing edge,
        // and if they are both oneway, it removes the vertex and adds a new edge between the two remaining vertices
        for (const auto& vertex : vertices) {
            unsigned long vid = vertex.GetId();
            if (marked.count(vid)) continue;

            list<Edges> outEdges = vertex.GetEdges();

            vector<pair<unsigned long, Edges>> inEdges;
            auto inIt = inMap.find(vid);
            if (inIt != inMap.end()) inEdges = inIt->second;

            if (outEdges.size() == 1 && inEdges.size() == 1) {
                const Edges& outE = outEdges.front();
                const Edges& inE  = inEdges[0].second;
                
                if (outE.GetOneway() && inE.GetOneway()) {
                    unsigned long A = inEdges[0].first;
                    unsigned long B = outE.GetEndId();
                    if (A != B && !marked.count(A) && !marked.count(B)) {
                        double latA = vertices[vertex_id.at(A)].GetLatitude();
                        double lonA = vertices[vertex_id.at(A)].GetLongitude();
                        double latB = vertices[vertex_id.at(B)].GetLatitude();
                        double lonB = vertices[vertex_id.at(B)].GetLongitude();
                        double latM = vertex.GetLatitude();
                        double lonM = vertex.GetLongitude();

                        double h_AM = harvesine(latA, lonA, latM, lonM);
                        double factor = (h_AM > 0.0) ? (inE.GetDistance() / h_AM) : 1.0;

                        double newDist = factor * harvesine(latA, lonA, latB, lonB);
                        
                        eSrc.push_back(A);
                        eDst.push_back(B);
                        eDist.push_back(newDist);
                        eOneway.push_back(true);
                        toRemove.push_back(vid);
                        marked.insert(vid);
                        changed = true;
                    }
                }
            }
            // Checks for vertices that have two incoming and two outgoing edges, 
            // and if they are all bidirectional, it removes the vertex and 
            // adds new edges between the remaining vertices
            else if (outEdges.size() == 2 && inEdges.size() == 2) {
                bool allBidi = true;
                for (const auto& e : outEdges)
                    if (e.GetOneway()) { allBidi = false; break; }
                if (allBidi)
                    for (const auto& p : inEdges)
                        if (p.second.GetOneway()) { allBidi = false; break; }

                if (allBidi) {
                    unsigned long A = inEdges[0].first;
                    unsigned long B = inEdges[1].first;

                    auto oit  = outEdges.begin();
                    unsigned long o1 = oit->GetEndId(); ++oit;
                    unsigned long o2 = oit->GetEndId(); 

                    bool outMatchesIn = (o1 == A && o2 == B) || (o1 == B && o2 == A);

                    // If the outgoing edges match the incoming edges and are bidirectional,
                    // we can safely remove the vertex and connect A and B directly
                    if (outMatchesIn && A != B && !marked.count(A) && !marked.count(B)) {
                        double latA = vertices[vertex_id.at(A)].GetLatitude();
                        double lonA = vertices[vertex_id.at(A)].GetLongitude();
                        double latB = vertices[vertex_id.at(B)].GetLatitude();
                        double lonB = vertices[vertex_id.at(B)].GetLongitude();
                        double latM = vertex.GetLatitude();
                        double lonM = vertex.GetLongitude();

                        double dAV = inEdges[0].second.GetDistance();
                        
                        double h_AM = harvesine(latA, lonA, latM, lonM);
                        double factor = (h_AM > 0.0) ? (dAV / h_AM) : 1.0;
                        
                        double newDist = factor * harvesine(latA, lonA, latB, lonB);

                        eSrc.push_back(A);
                        eDst.push_back(B);
                        eDist.push_back(newDist);
                        eOneway.push_back(false);
                        toRemove.push_back(vid);
                        marked.insert(vid);
                        changed = true;
                    }
                }
            }
        }
 
        for (size_t i = 0; i < eSrc.size(); i++) {
            AddEdge(eSrc[i], eDst[i], eDist[i], eOneway[i]);
        }
        for (unsigned long id : toRemove) {
            if (vertex_id.count(id)) {
                removeVertex(id);
            }
        }
    }
}