#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>
#include <map>

using std::cout;
using std::endl;

/**
 * 基本方法：
 *   抽象方法：抽象类中声明，派生类中实现
 *   具体方法：抽象类中实现，派生类中覆写
 *   钩子方法：抽象类中实现，包括用于判断逻辑的和需要派生类中覆写的
*/
class AbstractClass {
public:
    virtual ~AbstractClass() {}

    virtual void TemplateMethod() {
        SpecificMethodA();
        if (HookMethodB()) {
            HookMethodA();
        }
        AbstractMethod();
        SpecificMethodB();
    }

protected:
    virtual void AbstractMethod() = 0;
    virtual void SpecificMethodA() {
        puts("This is AbstractClass::SpecificMethodA()!");
    }
    virtual void SpecificMethodB() {
        puts("This is AbstractClass::SpecificMethodB()!");
    }
    virtual void HookMethodA() {
        puts("This is AbstractClass::HookMethodA()!");
    }
    virtual bool HookMethodB() {
        return false;
    }
};

class ConcreteClass : public AbstractClass {
public:
    void AbstractMethod() override {
        puts("This is ConcreteClass::AbstractMethod()!");
    }

protected:
    void SpecificMethodB() override {
        puts("This is ConcreteClass::SpecificMethodB()!");
    }

    void HookMethodA() override {
        puts("This is ConcreteClass::HookMethodA()");
    }

    bool HookMethodB() override {
        return true;
    }
};

int main() {
    std::unique_ptr<AbstractClass> ptr = std::make_unique<ConcreteClass>();
    ptr->TemplateMethod();
    return 0;
}
