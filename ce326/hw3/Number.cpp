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
            

            
        }
};