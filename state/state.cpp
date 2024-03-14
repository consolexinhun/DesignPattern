#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>
#include <map>

using std::cout;
using std::endl;

class AbstractState;

/**
 * 环境类，维护当前状态，并将与状态相关的操作委托给当前状态对象来处理
*/
class EnvContext {
public:
    EnvContext();
    void SetState(std::shared_ptr<AbstractState> state) {
        state_ = state;
    }
    std::shared_ptr<AbstractState> GetState() {
        return state_;
    }

    void Operation();

private:
    std::shared_ptr<AbstractState> state_ = nullptr;
};

class AbstractState {
public:
    virtual ~AbstractState() {}
    virtual void Operation(EnvContext* context) = 0;
};

class ConcreteStateA : public AbstractState {
public:
    void Operation(EnvContext* context) override;
};

class ConcreteStateB : public AbstractState {
public:
    void Operation(EnvContext* context) override;
};

EnvContext::EnvContext() {
    state_.reset(new ConcreteStateA());
}

void EnvContext::Operation() {
    state_->Operation(this);
}

void ConcreteStateA::Operation(EnvContext* context) {
    printf("Now your state is A\n");
    // 改变状态
    std::shared_ptr<AbstractState> state = std::make_shared<ConcreteStateB>();
    context->SetState(state);
}

void ConcreteStateB::Operation(EnvContext* context) {
    printf("Now tour state is B\n");
    std::shared_ptr<AbstractState> state = std::make_shared<ConcreteStateA>();
    context->SetState(state);
}

int main() {
    std::shared_ptr<EnvContext> context = std::make_shared<EnvContext>();
    context->Operation();
    context->Operation();
    context->Operation();
    context->Operation();
    return 0;
}
