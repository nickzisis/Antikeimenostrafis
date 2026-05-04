#ifndef OBJECTARRAY_HPP
#define OBJECTARRAY_HPP

#include "Object.hpp"

class ObjectArray : public Object {
    virtual void print() const = 0; // Pure virtual function
    virtual ~Object() {}            // Virtual destructor
    virtual bool isEqual(const Object* other) const = 0;
    virtual std::shared_ptr<Object> operator+(const Object& other) const = 0;
    virtual std::shared_ptr<Object> operator^(const Object& needle) const = 0;
    virtual std::shared_ptr<Object> clone() const = 0;
    virtual std::shared_ptr<Object> operator[](int index) const = 0;
};

#endif