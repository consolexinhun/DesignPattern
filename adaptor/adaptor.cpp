#include <iostream>
#include <memory>
#include <string>
#include <cstdio>

using std::cout;
using std::endl;

/**
 * @brief 目标接口
 * 
 */
class AbstructTarget {
public:
    virtual void Request() = 0;
};

/**
 * @brief 适配器，把接口转为目标接口
 * 
 */
class Adaptee {
public:
    void SpecificRequest() {
        puts("This is Adaptee::SpecificRequest()");
    }
};

class Adaptor : public AbstructTarget {
public:
    Adaptor() {
        adaptee_ = std::make_unique<Adaptee>();
    }
    void Request() override {
        adaptee_->SpecificRequest();
    }
private:
    std::unique_ptr<Adaptee> adaptee_;
};

int main() {
    std::shared_ptr<Adaptor> adaptor = std::make_shared<Adaptor>();
    adaptor->Request();
    return 0;
}
