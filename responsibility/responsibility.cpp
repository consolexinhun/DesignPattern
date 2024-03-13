#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>
#include <map>

using std::cout;
using std::endl;

/**
 * 抽象处理者，定义处理请求的接口，包含抽象处理方法和后继链接
*/
class AbstractHandler {
public:
    virtual ~AbstractHandler() {}
    virtual void SetNext(AbstractHandler* handler) {
        next_ = handler;
    }
    virtual AbstractHandler* GetNext() {
        return next_;
    }
    virtual void Request(const std::string& state) = 0;

private:
    AbstractHandler* next_;
};

/**
 * 具体处理者，判断能否处理此次请求，如果不能，则将请求转给它的后继
*/
class ConcreteHandlerA : public AbstractHandler {
public:
    void Request(const std::string& state) override {
        if (state.compare("A") == 0) {
            printf("This is ConcreteHandlerA::Request()\n");
        } else {
            if (GetNext()) {
                GetNext()->Request(state);
            } else {
                printf("From A , nobody handle this request\n");
            }
        }
    }
};

class ConcreteHandlerB : public AbstractHandler {
public:
    void Request(const std::string& state) override {
        if (state.compare("B") == 0) {
            printf("This is ConcreteHandlerB::Request()\n");
        } else {
            if (GetNext()) {
                GetNext()->Request(state);
            } else {
                printf("From B, nobody handle this request\n");
            }
        }
    }
};




int main() {
    std::shared_ptr<AbstractHandler> ptr_a = std::make_shared<ConcreteHandlerA>();
    std::shared_ptr<AbstractHandler> ptr_b = std::make_shared<ConcreteHandlerB>();
    ptr_a->SetNext(ptr_b.get());
    ptr_a->Request("B");
    return 0;
}
