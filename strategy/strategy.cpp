#include <iostream>
#include <memory>
#include <string>
#include <cstdio>

using std::cout;
using std::endl;

/**
 * @brief 抽象策略，定义公共接口
 * 
 */
class AbstractStrategy {
public:
    virtual ~AbstractStrategy() {}
    virtual void StrategyMethod() = 0;
};


/**
 * @brief 具体策略类
 * 
 */
class ConcreteStrategyA : public AbstractStrategy {
public:
    void StrategyMethod() override {
        printf("This is ConcreteStrategyA::StrategyMethod!\n");
    }
};

class ConcreteStrategyB : public AbstractStrategy {
public:
    void StrategyMethod() override {
        printf("This is ConcreteStrategyB::StrategyMethod!\n");
    }
};


/**
 * @brief 持有策略的引用，给客户端调用
 * 
 */
class Context {
public:
    void SetStrategy(AbstractStrategy* strategy) {
        strategy_ = strategy;
    }
    void StrategyMethod() {
        if (strategy_) {
            strategy_->StrategyMethod();
        }
    }

private:
    AbstractStrategy* strategy_ = nullptr;
};

int main() {
    std::unique_ptr<AbstractStrategy> strategyA = std::make_unique<ConcreteStrategyA>();
    std::unique_ptr<AbstractStrategy> strategyB = std::make_unique<ConcreteStrategyB>();

    Context context;
    context.SetStrategy(strategyA.get());
    context.StrategyMethod();

    context.SetStrategy(strategyB.get());
    context.StrategyMethod();
    return 0;
}
