#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;

class Product {
public:
    Product() = default;

    virtual ~Product() {}
};

class ConcreteProductA : public Product {
public:
    ConcreteProductA() = default;

    ~ConcreteProductA() override {
        cout << "Destruct ConcreteProduct A" << endl;
    }
};

class ConcreteProductB : public Product {
public:
    ConcreteProductB() = default;

    ~ConcreteProductB() override {
        cout << "Destruct ConcreteProduct B" << endl;
    }
};

class Factory {
public:
    std::shared_ptr<Product> createProduct(std::string product_name) {
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
    std::shared_ptr<Product> a = factory.createProduct("A");
    std::shared_ptr<Product> b = factory.createProduct("B");
    return 0;
}
