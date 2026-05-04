#ifndef NUMBER_HPP
#define NUMBER_HPP

#include "Object.hpp"
#include "ObjectArray.hpp"
#include "String.hpp"

class Number : public Object {
    private:
        double value;
    public:
        Number(double val);
        ~Number() {};

        void SetValue(double value);
        double GetValue() const;

        void print() const override;
        bool isEqual(const Object* other) const override;
        std::shared_ptr<Object> operator[](int index) const override;
        std::shared_ptr<Object> operator^(const Object& needle) const override;
        std::shared_ptr<Object> operator+(const Object& other) const override;
        std::shared_ptr<Object> clone() const override;
};

#endif