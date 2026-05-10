#include "Number.hpp"
#include "String.hpp"
#include "ObjectArray.hpp"

String::String(const string& val) : value(val) {}

String::~String() {} 

void String::SetValue(const string& value) {
    this->value = value;   
}     

string String::GetValue() const {
    return value;
}

void String::print() const {
    cout << "\"" << value << "\"";
}

bool String::isEqual(const Object* other) const {
    const String* otherString = dynamic_cast<const String*>(other);

    if (otherString) {
        if (this->value == otherString->value) {
            return true;
        }
    }
    return false;
}

shared_ptr<Object> String::operator[](int index) const {
    if (index < 0 || index >= static_cast<int>(value.size())) {
        cout << "Error: Index out of bounds." << endl;
        return nullptr;
    }
    return make_shared<String>(string(1, value[index]));
}

shared_ptr<Object> String::operator^(const Object& needle) const {
    const Number* needleNum = dynamic_cast<const Number*>(&needle);
    const ObjectArray* needleArray = dynamic_cast<const ObjectArray*>(&needle);

    if (needleNum) {
        cout << "Error: Searching Number on String is not defined." << endl;
        return nullptr;
    }

    if(needleArray) {
        cout << "Error: Searching ObjectArray on String is not defined." << endl;
        return nullptr;
    }
    
    const String* needleString = dynamic_cast<const String*>(&needle);
    shared_ptr<ObjectArray> resultArray = make_shared<ObjectArray>();

    size_t pos = 0;
    while ((pos = value.find(needleString->value, pos)) != string::npos) {
        resultArray->addElement(make_shared<Number>(static_cast<double>(pos)));
        pos++;
    }
    
    return resultArray;
}

shared_ptr<Object> String::operator+(const Object& other) const {
    const String* otherString = dynamic_cast<const String*>(&other);
    
    if (!otherString) {
        cout << "Error: Addition not defined between incompatible types." << endl;
        return nullptr;
    }

    return make_shared<String>(value + otherString->value);
}

shared_ptr<Object> String::clone() const {
    return make_shared<String>(value);
}