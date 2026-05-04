#ifndef OBJECTARRAY_HPP
#define OBJECTARRAY_HPP

#include "Number.hpp"
#include "String.hpp"
#include "Object.hpp"
using namespace std;

class ObjectArray : public Object {
    private:
        vector<shared_ptr<Object>> elements;
    public:
        ObjectArray();
        ~ObjectArray() {};
        void print() const override;
        bool isEqual(const Object* other) const override;
        shared_ptr<Object> operator+(const Object& other) const override;
        shared_ptr<Object> operator^(const Object& needle) const override;
        shared_ptr<Object> clone() const override;
        shared_ptr<Object> operator[](int index) const override;
        int getSize();
};

#endif