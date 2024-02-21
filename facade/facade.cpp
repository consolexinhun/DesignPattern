#include <iostream>
#include <memory>
#include <string>
#include <cstdio>

using std::cout;
using std::endl;

class SubModuleA {
public:
    void PreRequest() {
        puts("SubModuleA::PreRequest()!");
    }
};

class SubModuleB {
public:
    void RealRequest() {
        puts("SubModuleB::RealRequest()!");
    }
};

class SubModuleC {
public:
    void PostRequest() {
        puts("SubModuleC::PostRequest()!");
    }
};

class Facade {
public:
    Facade() {
        a_ = std::make_shared<SubModuleA>();
        b_ = std::make_shared<SubModuleB>();
        c_ = std::make_shared<SubModuleC>();
    }

    void Request() {
        a_->PreRequest();
        b_->RealRequest();
        c_->PostRequest();
    }

private:
    std::shared_ptr<SubModuleA> a_;
    std::shared_ptr<SubModuleB> b_;
    std::shared_ptr<SubModuleC> c_;
};

int main() {
    std::shared_ptr<Facade> facade = std::make_shared<Facade>();
    facade->Request();
    return 0;
}
