#ifndef OBJECT_ARRAY_HPP
#define OBJECT_ARRAY_HPP

#include "ObjectArray.hpp"

class ObjectArray : public Object {
    private:
        vector<shared_ptr<Object>> elements;
    public:
        ObjectArray() {};

        ~ObjectArray() {};

        void print() const override {
            cout << "{";
            for (size_t i = 0; i < elements.size(); ++i) {
                elements[i]->print();
                if (i < elements.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "}";
            cout << endl;       
        };

        bool isEqual(const Object* other) const override {
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

        shared_ptr<Object> operator+(const Object& other) const override {
            shared_ptr<ObjectArray> newArray = make_shared<ObjectArray>();
            newArray->elements = this->elements;
            newArray->elements.push_back(other.clone());
            return newArray;
        };
        
        shared_ptr<Object> operator^(const Object& needle) const override {
            const Number* needleNumber = dynamic_cast<const Number*>(&needle);
            const String* needleString = dynamic_cast<const String*>(&needle);
            const ObjectArray* needleArray = dynamic_cast<const ObjectArray*>(&needle);

            if (needleNumber){
                vector<Number> resultArray = {};
                for (int i = 0; i < elements.size(); ++i){
                    
                    if (elements[i]->isEqual(needleNumber)){
                        resultArray.push_back(Number(i));
                    }
                    
                }
            }
        };
        
        vector<Number> numberSearch(ObjectArray& array, Number& needle, vector<Number>& resultArray){
            for (int i = 0; i < array.getSize(); i++){
                if (array[i]->isEqual(dynamic_cast<Object*>(&needle))){

                }
            }
        };

        int getSize(){
            return elements.size();
        }
};

#endif