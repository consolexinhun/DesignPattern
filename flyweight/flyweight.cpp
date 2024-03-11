#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <map>

using std::cout;
using std::endl;

/**
 * 非享元类，以参数形式注入具体享元的相关方法
*/
class UnsharableConcreteFlyweight {
public:    
    UnsharableConcreteFlyweight(const std::string& content) : content_(content) {}
    const std::string& GetContent() const { 
        return content_;
    }
private:
    std::string content_;
};

/**
 * 抽象享元类
*/
class AbstractFlyweight {
public:
    virtual ~AbstractFlyweight() {}
    virtual void Run(UnsharableConcreteFlyweight* ptr) = 0;
};

class ConcreteFlyweightA : public AbstractFlyweight {
public:
    void Run(UnsharableConcreteFlyweight* ptr) override {
        puts("ConcreteFlyweightA::Run()!");
        printf("%s\n", ptr->GetContent().c_str());
    }
};

class ConcreteFlyweightB : public AbstractFlyweight {
public:
    void Run(UnsharableConcreteFlyweight* ptr) override {
        puts("ConcreteFlyweightB::Run()!");
        printf("%s\n", ptr->GetContent().c_str());
    }
};

class FlyweightFactory {
public:
    enum FlyweightType {
        ConcreteA = 0,
        ConcreteB,
    };

    ~FlyweightFactory() {}

    std::shared_ptr<AbstractFlyweight> GetFlyweight(const std::string& key, const FlyweightType& type = ConcreteA) {
        auto it = m_flyweights_.find(key);
        if (it == m_flyweights_.end()) {
            if (type == ConcreteA) {
                m_flyweights_.emplace(key, std::make_shared<ConcreteFlyweightA>());
            } else if (type == ConcreteB) {
                m_flyweights_.emplace(key, std::make_shared<ConcreteFlyweightB>());
            }
        }
        return m_flyweights_[key];
    }

private:
    std::map<std::string, std::shared_ptr<AbstractFlyweight>> m_flyweights_; 
};

int main() {
    std::shared_ptr<UnsharableConcreteFlyweight> ptr1 = std::make_shared<UnsharableConcreteFlyweight>("UnsharableFlyweight_ptr1");
    std::shared_ptr<UnsharableConcreteFlyweight> ptr2 = std::make_shared<UnsharableConcreteFlyweight>("UnsharableFlyweight_ptr2");

    std::shared_ptr<FlyweightFactory> factory = std::make_shared<FlyweightFactory>();
    std::shared_ptr<AbstractFlyweight> A_red = factory->GetFlyweight("Red");
    std::shared_ptr<AbstractFlyweight> A_point = factory->GetFlyweight("Point");

    A_red->Run(ptr1.get());
    A_point->Run(ptr2.get());
    return 0;
}
