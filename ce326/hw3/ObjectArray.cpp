#include "Number.hpp"
#include "String.hpp"
#include "ObjectArray.hpp"

ObjectArray::ObjectArray() {};

int ObjectArray::getSize() const {
    return elements.size();
}

void ObjectArray::addElement(shared_ptr<Object> elem) {
    elements.push_back(elem);
}

void ObjectArray::print() const {
    cout << "{";
    for (size_t i = 0; i < elements.size(); ++i) {
        elements[i]->print();
        if (i < elements.size() - 1) {
            cout << ", ";
        }
    }
    cout << "}";       
};

bool ObjectArray::isEqual(const Object* other) const {
    const ObjectArray* otherArray = dynamic_cast<const ObjectArray*>(other);
    
    if (!otherArray) {
        return false;
    }
    
    if (this->elements.size() != otherArray->elements.size()) {
        return false;
    }
    
    for (size_t i = 0; i < elements.size(); ++i) {
        if (!this->elements[i]->isEqual(otherArray->elements[i].get())) {
            return false;
        }
    }
    return true;
};

shared_ptr<Object> ObjectArray::clone() const {
    shared_ptr<ObjectArray> newArray = make_shared<ObjectArray>();
    
    for (const shared_ptr<Object>& elem : elements) {
        newArray->addElement(elem->clone());
    }
    
    return newArray;
}

shared_ptr<Object> ObjectArray::operator[](int index) const {
    if ((index < 0) || (index >= (int)elements.size())) {
        cout << "Error: Index out of bounds." << endl;
        return nullptr;
    }

    return elements[index];
}

shared_ptr<Object> ObjectArray::operator+(const Object& other) const {
    const ObjectArray* otherArray = dynamic_cast<const ObjectArray*>(&other);

    if (!otherArray) {
        cout << "Error: Addition not defined between incompatible types." << endl;
        return nullptr;
    }

    shared_ptr<ObjectArray> newArray = make_shared<ObjectArray>();

        for (const auto& elem : elements) {
            newArray->addElement(elem->clone());
        }

        for (const auto& elem : otherArray->elements){
            newArray->addElement(elem->clone());
        }
    
    return newArray;
};

void ObjectArray::searchPaths(const Object* needle, vector<int>& currentPath,
                                shared_ptr<ObjectArray> results) const {
    
    for (int i = 0; i < (int)elements.size(); ++i) {
        currentPath.push_back(i);
        
        if (elements[i]->isEqual(needle)) {
            shared_ptr<ObjectArray> path = make_shared<ObjectArray>();
        
            for (int idx : currentPath) {
                path->addElement(make_shared<Number>(static_cast<double>(idx)));
            }
        
            results->addElement(path);
        }

        const ObjectArray* subArray = dynamic_cast<const ObjectArray*>(elements[i].get());
        
        if (subArray) {
            subArray->searchPaths(needle, currentPath, results);
        }
        
        currentPath.pop_back();
    }
}

void ObjectArray::searchArrayPaths(const ObjectArray* needle, vector<int>& currentPath,
                                    shared_ptr<ObjectArray> results) const{
    
    for (int i = 0; i <= (int)elements.size() - (int)needle->elements.size(); ++i) {
        bool match = true;
        
        for (int j = 0; j < (int)needle->elements.size(); ++j) {
            if (!elements[i+j]->isEqual(needle->elements[j].get())) {
                match = false;
                break;
            }
        }
        
        if (match) {
            shared_ptr<ObjectArray> path = make_shared<ObjectArray>();
            for (int idx : currentPath) {
                path->addElement(make_shared<Number>(static_cast<double>(idx)));
            }
            results->addElement(path);
        }
    }

    for (int i = 0; i < (int)elements.size(); ++i) {
        const ObjectArray* subArray = dynamic_cast<const ObjectArray*>(elements[i].get());
        
        if (subArray) {
            currentPath.push_back(i);
            subArray->searchArrayPaths(needle, currentPath, results);
            currentPath.pop_back();
        }
    }
}

shared_ptr<Object> ObjectArray::operator^(const Object& needle) const {
    if (dynamic_cast<const String*>(&needle)) {
        shared_ptr<ObjectArray> results = make_shared<ObjectArray>();
        vector<int> path;
        
        searchPaths(&needle, path, results);
        return results;
    }

    else if (dynamic_cast<const Number*>(&needle)) {
        shared_ptr<ObjectArray> results = make_shared<ObjectArray>();
        vector<int> path;
        
        searchPaths(&needle, path, results);
        if (results->getSize() == 0) {
            auto notFound = make_shared<ObjectArray>();
            
            notFound->addElement(make_shared<Number>(-1.0));
            results->addElement(notFound);
        }
        
        return results;
    }

    else if (const ObjectArray* needleArray = dynamic_cast<const ObjectArray*>(&needle)) {
        shared_ptr<ObjectArray> results = make_shared<ObjectArray>();
        vector<int> path;
        
        searchArrayPaths(needleArray, path, results);
        
        return results;
}
    
    return nullptr;
}