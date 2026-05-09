#include "Number.hpp"
#include "String.hpp"
#include "ObjectArray.hpp"

Number::Number(double val) : value(val) {}

void Number::SetValue(double value) {
    this->value = value;   
}     

double Number::GetValue() const {
    return value;
}

void Number::print() const {
    cout << value;
}

bool Number::isEqual(const Object* other) const {
    const Number* otherNumber = dynamic_cast<const Number*>(other);

    if (otherNumber) {
        if (this->value == otherNumber->value) {
            return true;
        }
    }
    return false;
}

shared_ptr<Object> Number::operator[](int) const {

    cout << "Error: Number type is not indexable." << endl;
    return nullptr;
}

shared_ptr<Object> Number::operator^(const Object& needle) const {
    const Number* otherNumber = dynamic_cast<const Number*>(&needle);
    const String* otherString = dynamic_cast<const String*>(&needle);
    const ObjectArray* otherArray = dynamic_cast<const ObjectArray*>(&needle);

    if (otherNumber) {
        cout << "Error: Searching Number on Number is not defined." << endl;
        return nullptr;
    }
    else if (otherString) {
        cout << "Error: Searching String on Number is not defined." << endl;
        return nullptr;
    }
    else if (otherArray) {
        cout << "Error: Searching ObjectArray on Number is not defined." << endl;
        return nullptr;
    }

    return nullptr;
}

shared_ptr<Object> Number::operator+(const Object& other) const {
    const Number* otherNumber = dynamic_cast<const Number*>(&other);
    
    if (!(otherNumber)) {
        cout << "Error: Addition not defined between incompatible types." << endl;
        return nullptr;
    }
    else {
        return make_shared<Number>(this->value + otherNumber->value);
    }
}

shared_ptr<Object> Number::clone() const {
    return make_shared<Number>(this->value);
}