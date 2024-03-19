#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>
#include <map>
#include <list>

using std::cout;
using std::endl;

class AbstractMediator;

/**
 * 定义抽象同事类，保存中介者对象
*/
class AbstractColleague {
public:
    virtual ~AbstractColleague() {}

    virtual void Send() = 0;
    virtual void Receive() = 0;

    void SetMedium(AbstractMediator* mediator) {
        mediator_ = mediator;
    }

protected:
    AbstractMediator* mediator_ = nullptr;
};

/**
 * 具体同事类：由中介者负责和其他同事类的交互
*/
class ConcreteColleagueA : public AbstractColleague {
public:
    void Send() override;
    void Receive() override;
};

class ConcreteColleagueB : public AbstractColleague {
public:
    void Send() override;
    void Receive() override;
};

/**
 * 抽象中介类：注册同事对象，转发同事对象信息
*/
class AbstractMediator {
public:
    virtual ~AbstractMediator() {}

    // 注册
    virtual void Register(AbstractColleague* colleague) = 0;
    // 转发
    virtual void Reply(AbstractColleague* colleague) = 0;
};

class ConcreteMediator : public AbstractMediator {
public:
    void Register(AbstractColleague* colleague) override {
        for (auto it : colleagues_) {
            if (it == colleague) return;
        }
        colleagues_.emplace_back(colleague);
        // 设置中介者
        colleague->SetMedium(this);
    }

    void Reply(AbstractColleague* colleague) override {
        // 转发给其他同事
        for (auto it : colleagues_) {
            if (it != colleague) {
                it->Receive();
            }
        }
    }

private:
    std::list<AbstractColleague*> colleagues_;
};

// 具体同事类的实现
void ConcreteColleagueA::Receive() {
    printf("This is ConcreteColleagueA::Receive()\n");
}
void ConcreteColleagueA::Send() {
    printf("This is ConcreteColleagueA::Send()\n");

    // 中介者转发
    mediator_->Reply(this);
}

void ConcreteColleagueB::Receive() {
    printf("This is ConcreteColleagueB::Receive()\n");
}
void ConcreteColleagueB::Send() {
    printf("This is ConcreteColleagueB::Send()\n");
    mediator_->Reply(this);
}

int main() {
    std::shared_ptr<AbstractMediator> mediator = std::make_shared<ConcreteMediator>();

    std::shared_ptr<AbstractColleague> colleagueA = std::make_shared<ConcreteColleagueA>();
    std::shared_ptr<AbstractColleague> colleagueB = std::make_shared<ConcreteColleagueB>();

    mediator->Register(colleagueA.get());
    mediator->Register(colleagueB.get());

    colleagueA->Send();
    printf("\n\n\n");
    colleagueB->Send();
    return 0;
}
