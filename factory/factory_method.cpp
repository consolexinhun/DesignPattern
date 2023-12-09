#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;

class Product {
public:
    virtual ~Product() {}
};

class ConcreteProductA : public Product {
public:
    ~ConcreteProductA() override {
        cout << "Destruct ConcreteProduct A" << endl;
    }
};

class ConcreteProductB : public Product {
public:
    ~ConcreteProductB() override {
        cout << "Destruct ConcreteProduct B" << endl;
    }
};

class Factory {
public:
    virtual ~Factory() {}
    virtual std::shared_ptr<Product> CreateProduct() = 0;
};

class ConcreteFactoryA : public Factory {
public:
    ~ConcreteFactoryA() override {
        cout << "Destruct ConcreteFactory A" << endl;
    }
    std::shared_ptr<Product> CreateProduct() override {
        return std::shared_ptr<Product>(new ConcreteProductA());
    }
};

class ConcreteFactoryB : public Factory {
public:
    ~ConcreteFactoryB() override {
        cout << "Destruct ConcreteFactory B" << endl;
    }
    std::shared_ptr<Product> CreateProduct() override {
        return std::shared_ptr<Product>(new ConcreteProductB());
    }
};

int main() {
    std::shared_ptr<Factory> fa(new ConcreteFactoryA());
    std::shared_ptr<Product> pa = fa->CreateProduct();

    std::shared_ptr<Factory> fb(new ConcreteFactoryB());
    std::shared_ptr<Product> pb = fb->CreateProduct();
    return 0;
}
