#ifndef OBJECTARRAY_HPP
#define OBJECTARRAY_HPP
#include "Object.hpp"
using namespace std;

class ObjectArray : public Object {
    private:
        vector<shared_ptr<Object>> elements;
    public:
        ObjectArray();
        ~ObjectArray() {};
        int getSize() const;
        void addElement(shared_ptr<Object> elem);
        void print() const override;
        bool isEqual(const Object* other) const override;
        void searchPaths(const Object* needle, vector<int>& currentPath, shared_ptr<ObjectArray> results) const;
        void searchArrayPaths(const ObjectArray* needle, vector<int>& currentPath, shared_ptr<ObjectArray> results) const;
        shared_ptr<Object> operator+(const Object& other) const override;
        shared_ptr<Object> operator^(const Object& needle) const override;
        shared_ptr<Object> clone() const override;
        shared_ptr<Object> operator[](int index) const override;
};

#endif