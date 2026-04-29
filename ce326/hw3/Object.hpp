#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Η βασική κλάση
class Object {
public:
    virtual void print() const = 0; // Pure virtual function
    virtual ~Object() {}            // Virtual destructor
    virtual bool isEqual(const Object* other) const = 0;
    virtual std::shared_ptr<Object> operator+(const Object& other) const = 0;
    virtual std::shared_ptr<Object> operator^(const Object& needle) const = 0;
    virtual std::shared_ptr<Object> clone() const = 0;
    virtual std::shared_ptr<Object> operator[](int index) const = 0;
};

#endif
