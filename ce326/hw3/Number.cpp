#include "Number.hpp"

class Number : public Object {
    private:
        double value;
    public:
        Number(double val) : value(val) {}
        
        ~Number() {}

        void SetValue(double value) {
            this->value = value;   
        }     
        
        double GetValue() const {
            return value;
        }

        void print() const override {
            std::cout << value;
        }

        bool isEqual(const Object* other) const override {
            const Number* otherNumber = dynamic_cast<const Number*>(other);

            if (otherNumber) {
                if (this->value == otherNumber->value) {
                    return true;
                }
            }
            return false;
        }

        std::shared_ptr<Object> operator[](int index) const override {
            std::cout << "Error: Number type is not indexable." << std::endl;
            return nullptr;
        }

        std::shared_ptr<Object> operator^(const Object& needle) const override {
            
            if (const Number* otherNumber = dynamic_cast<const Number*>(&needle)) {
                std::cout << "Error: Searching Number on Number is not defined." << std::endl;
                return nullptr;
            }
            else if (const String* otherString = dynamic_cast<const String*>(&needle)) {
                std::cout << "Error: Searching String on Number is not defined." << std::endl;
                return nullptr;
            }
            else if (const ObjectArray* otherArray = dynamic_cast<const ObjectArray*>(&needle)) {
                std::cout << "Error: Searching ObjectArray on Number is not defined." << std::endl;
                return nullptr;
            }
        }

        std::shared_ptr<Object> operator+(const Object& other) const override {
            const Number* otherNumber = dynamic_cast<const Number*>(&other);
            
            if (!(otherNumber)) {
                std::cout << "Error: Addition not defined between incompatible types." << std::endl;
                return nullptr;
            }
            else {
                return std::make_shared<Number>(this->value + otherNumber->value);
            }
        }

        std::shared_ptr<Object> clone() const override {
            return std::make_shared<Number>(this->value);
        }
        
};