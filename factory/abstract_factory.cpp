#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;

class ProductA {
public:
    virtual ~ProductA() {}
};

class ProductB {
public:
    virtual ~ProductB() = default;
};

class ConcreteProductA1 : public ProductA {
public:
    ~ConcreteProductA1() override {
        cout << "Destruct ConcreteProduct A1" << endl;
    }
};

class ConcreteProductA2 : public ProductA {
public:
    ~ConcreteProductA2() override {
        cout << "Destruct ConcreteProduct A2" << endl;
    }
};

class ConcreteProductB1 : public ProductB {
public:
    ~ConcreteProductB1() override {
        cout << "Destruct ConcreteProduct B1" << endl;
    }
};

class ConcreteProductB2 : public ProductB {
public:
    ~ConcreteProductB2() override {
        cout << "Destruct ConcreteProduct B2" << endl;
    }
};

class Factory {
public:
    virtual ~Factory() {}
    virtual std::shared_ptr<ProductA> CreateProductA() = 0;
    virtual std::shared_ptr<ProductB> CreateProductB() = 0;
};

class ConcreteFactory1 : public Factory {
public:
    ~ConcreteFactory1() override {
        cout << "Destruct ConcreteFactory 1" << endl;
    }
    std::shared_ptr<ProductA> CreateProductA() override {
        return std::shared_ptr<ProductA>(new ConcreteProductA1());
    }
    std::shared_ptr<ProductB> CreateProductB() override {
        return std::shared_ptr<ProductB>(new ConcreteProductB1());
    }
};

class ConcreteFactory2 : public Factory {
public:
    ~ConcreteFactory2() override {
        cout << "Destruct ConcreteFactory 2" << endl;
    }
    std::shared_ptr<ProductA> CreateProductA() override {
        return std::shared_ptr<ProductA>(new ConcreteProductA2());
    }
    std::shared_ptr<ProductB> CreateProductB() override {
        return std::shared_ptr<ProductB>(new ConcreteProductB2());
    }
};

int main() {
    std::shared_ptr<Factory> f1(new ConcreteFactory1());
    std::shared_ptr<ProductA> pa1 = f1->CreateProductA();
    std::shared_ptr<ProductB> pb1 = f1->CreateProductB();

    std::shared_ptr<Factory> f2(new ConcreteFactory2());
    std::shared_ptr<ProductA> pa2 = f2->CreateProductA();
    std::shared_ptr<ProductB> pb2 = f2->CreateProductB();
    return 0;
}
