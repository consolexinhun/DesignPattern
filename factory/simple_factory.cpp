#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;

class Product {
public:
    Product() = default;

    virtual ~Product() = default;
};

class ConcreteProductA : public Product {
public:
    ConcreteProductA() = default;

    ~ConcreteProductA() {
        cout << "Destruct ConcreteProduct A" << endl;
    }
};

class ConcreteProductB : public Product {
public:
    ConcreteProductB() = default;

    ~ConcreteProductB() {
        cout << "Destruct ConcreteProduct B" << endl;
    }
};

class Factory {
public:
    std::shared_ptr<Product> CreateProduct(std::string product_name) {
        if (product_name == "A") {
            return std::shared_ptr<Product>(new ConcreteProductA());
        } else if (product_name == "B") {
            return std::shared_ptr<Product>(new ConcreteProductB());
        } else {
            return nullptr;
        }
    }
};

int main() {
    Factory factory;
    std::shared_ptr<Product> a = factory.CreateProduct("A");
    std::shared_ptr<Product> b = factory.CreateProduct("B");
    return 0;
}
