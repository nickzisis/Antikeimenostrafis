#include "String.hpp"

class String : public Object {
    private:
        string value;
    public:
        String(const string& val) : value(val) {}
        
        ~String() {}

        void SetValue(const string& value) {
            this->value = value;   
        }     
        
        string GetValue() const {
            return value;
        }

        void print() const override {
            cout << value;
        }

        bool isEqual(const Object* other) const override {
            const String* otherString = dynamic_cast<const String*>(other);

            if (otherString) {
                if (this->value == otherString->value) {
                    return true;
                }
            }
            return false;
        }

        shared_ptr<Object> operator[](int index) const override {
            if (index < 0 || index >= static_cast<int>(value.size())) {
                cout << "Error: Index out of bounds." << endl;
                return nullptr;
            }
            return make_shared<String>(string(1, value[index]));
        }

        shared_ptr<Object> operator^(const Object& needle) const override {
            const String* needleString = dynamic_cast<const String*>(&needle);
            
            if (!needleString) {
                cout << "Error: Needle must be a string." << endl;
                return nullptr;
            }
    
            shared_ptr<ObjectArray> resultArray = make_shared<ObjectArray>();

            size_t pos = -1;
            while ((pos = value.find(needleString->value, pos+1)) != string::npos) {
                resultArray->operator+(make_shared<Number>(pos));
            }

            resultArray->print();
            return resultArray;
        }

        shared_ptr<Object> operator+(const Object& other) const override {
            const String* otherString = dynamic_cast<const String*>(&other);
            
            if (!otherString) {
                cout << "Error: Can only concatenate with another string." << endl;
                return nullptr;
            }

            return make_shared<String>(value + otherString->value);
        }

        shared_ptr<Object> clone() const override {
            return make_shared<String>(value);
        }
};
