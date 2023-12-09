#include <iostream>

using std::cout;
using std::endl;

class ProtoType {
public:
    virtual ~ProtoType() {
        cout << "Destruct() ProtoType" << endl;
    }

    virtual ProtoType* Clone() = 0;

protected:
    ProtoType() = default;
};


class ConcreteProtoType: public ProtoType {
public:
    ConcreteProtoType() = default;

    ConcreteProtoType(const ConcreteProtoType& cp) {
        *this = cp;
        cout << "ConcretePrototype copy..." << endl;
    }
    ~ConcreteProtoType() {
        cout << "Destruct ConcreteProtoType" << endl;
    }

    ProtoType* Clone() override {
        return new ConcreteProtoType(*this);
    }
};

int main() {
    ProtoType* p = new ConcreteProtoType();
    ProtoType* p1 = p->Clone();
    ProtoType* p2 = p->Clone();
    delete p;
    delete p1;
    delete p2;
}
