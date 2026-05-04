#include "Object.hpp"

class Number : public Object {
    private:
        double value;
    public:
        Number(double val);
        void SetValue(double value);
        double GetValue() const;
        void print() const override;
};