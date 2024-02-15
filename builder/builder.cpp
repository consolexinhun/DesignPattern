#include <iostream>
#include <memory>
#include <string>
#include <cstdio>

using std::cout;
using std::endl;

class Product {
public:
    void Show() {
        cout << "Product" << endl;
    }
};

class AbstractBuilder {
public:
    AbstractBuilder() {
        product_.reset(new Product());
    }
    virtual ~AbstractBuilder() {}

    Product* GetResult() {
        return product_.get();
    }

    virtual void BuilderPartA() = 0;
    virtual void BuilderPartB() = 0;
    virtual void BuilderPartC() = 0;
protected:
    std::shared_ptr<Product> product_;
};

class ConcreteBuilder : public AbstractBuilder {
public:
    virtual void BuilderPartA() {
        cout << "Build PartA" << endl;
    }

    virtual void BuilderPartB() {
        cout << "Build PartB" << endl;
    }

    virtual void BuilderPartC() {
        cout << "Build PartC" << endl;
    }
};

class Director {
public:
    Director(AbstractBuilder* builder) : builder_(builder) {

    }
    Product* ConstructProduct() {
        builder_->BuilderPartA();
        builder_->BuilderPartB();
        builder_->BuilderPartC();
        return builder_->GetResult();
    }
private:
    AbstractBuilder* builder_;
};

int main() {
    std::shared_ptr<AbstractBuilder> builder(new ConcreteBuilder());
    std::shared_ptr<Director> director(new Director(builder.get()));
    Product* product = director->ConstructProduct();
    product->Show();
    return 0;
}
