#ifndef STRING_HPP
#define STRING_HPP
#include "Number.hpp"
#include "ObjectArray.hpp"
using namespace std;
#include "Object.hpp"

class String : public Object {
    private:
        string value;
    public:
        String(const string& val);
        ~String();
        void SetValue(const string& value);
        string GetValue() const;
        void print() const override;
        bool isEqual(const Object* other) const override;
        shared_ptr<Object> operator[](int index) const override;
        shared_ptr<Object> operator^(const Object& needle) const override;
        shared_ptr<Object> operator+(const Object& other) const override;
        shared_ptr<Object> clone() const override;
};

#endif