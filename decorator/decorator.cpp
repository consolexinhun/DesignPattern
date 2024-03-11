#include <iostream>
#include <memory>
#include <string>
#include <cstdio>

using std::cout;
using std::endl;

/**
 * @brief 抽象组件
 * 
 */
class AbstractComponent {
public:
    virtual ~AbstractComponent() {}
    virtual void Request() = 0;
};

/**
 * @brief 具体组件
 * 
 */
class ConcreteComponent : public AbstractComponent {
public:
    void Request() override {
        puts("ConcreteComponent::Request()");
    }
};

/**
 * @brief 抽象装饰
 * 
 */
class AbstractDecorator : public AbstractComponent {
public:
    AbstractDecorator(AbstractComponent* comp) : comp_(comp) {}
    virtual void Request() {
        if (comp_) {
            comp_->Request();
        }
    }
private:
    AbstractComponent* comp_;
};

/**
 * @brief 具体装饰
 * 
 */
class ConcreteDecoratorA : public AbstractDecorator {
public:
    ConcreteDecoratorA(AbstractComponent* comp) : AbstractDecorator(comp) {}

    void Request() override {
        PreRequest();
        AbstractDecorator::Request();
        PostRequest();
    }

private:
    void PreRequest() {
        puts("ConcreteDecoratorA::PreRequest");
    }
    void PostRequest() {
        puts("ConcreteDecoratorA::PostRequest");
    }
};

int main() {
    std::unique_ptr<AbstractComponent> comp = std::make_unique<ConcreteComponent>();
    comp->Request();
    // 原有组件功能不变

    // 对现有组件功能扩展
    std::unique_ptr<AbstractDecorator> decorator = std::make_unique<ConcreteDecoratorA>(comp.get());
    decorator->Request();

    return 0;
}
