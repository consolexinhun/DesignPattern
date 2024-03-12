#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>
#include <map>

using std::cout;
using std::endl;

/**
 * 这是简单命令的例子
 * 与组合模式结合可以实现宏命令
 * 与备忘录模式结合可以实现命令的撤销和恢复
*/

/**
 * 抽象命令，声明执行命令的接口
*/
class AbstractCommand {
public:
    virtual ~AbstractCommand() {}
    virtual void Execute() = 0;
};

/**
 * 命令接收者，执行接收命令的基本操作
*/
class Receiver {
public:
    void Action() {
        printf("This is Receiver::Action\n");
    }
};


/**
 * 具体命令，拥有接收者对象
*/
class ConcreteCommand : public AbstractCommand{
public:
    ConcreteCommand() {
        receiver_.reset(new Receiver());
    }

    void Execute() override {
        receiver_->Action();
    }

private:
    std::shared_ptr<Receiver> receiver_;
};

/**
 * 命令请求者
*/
class Invoke {
public:
    Invoke(AbstractCommand* cmd) : cmd_(cmd) {}
    void SetCommand(AbstractCommand* cmd) {
        cmd_ = cmd;
    }
    void Request() {
        cmd_->Execute();
    }
private:
    AbstractCommand* cmd_;
};

int main() {
    std::shared_ptr<AbstractCommand> cmd = std::make_shared<ConcreteCommand>();
    Invoke client(cmd.get());
    client.Request();
    return 0;
}
