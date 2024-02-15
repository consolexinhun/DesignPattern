#include <iostream>
#include <memory>
#include <string>
#include <cstdio>

using std::cout;
using std::endl;

// 抽象主题
class AbstractSubject {
public:
    virtual ~AbstractSubject() {}
    virtual void Request() = 0;
};

// 实际主题
class RealSubject : public AbstractSubject {
public:
    void Request() override {
        puts("RealSubject::Request()");
    }
};

// 代理类，内部包含真实主题的引用，可以访问，控制或者扩展真实主题
class SubjectProxy : public AbstractSubject {
public:
    SubjectProxy() {
        real_ = std::make_unique<RealSubject>();
    }
    void PreRequest() {
        puts("SubjectProxy::PreRequest()");
    }
    void Request() override {
        PreRequest();
        real_->Request();
        PostRequest();
    }
    void PostRequest() {
        puts("SubjectProxy::PostRequest()");
    }

private:
    std::unique_ptr<RealSubject> real_;
};

int main() {
    // std::unique_ptr<AbstractSubject> proxy = std::make_unique<SubjectProxy>();
    std::shared_ptr<AbstractSubject> proxy = std::make_shared<SubjectProxy>();
    proxy->Request();
    return 0;
}
