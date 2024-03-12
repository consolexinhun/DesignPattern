#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>
#include <map>

using std::cout;
using std::endl;

/**
 * 宏命令，即组合命令
*/

/**
 * 抽象命令
*/
class AbstractMacroCommand {
public:
    virtual ~AbstractMacroCommand() {}
    virtual void Execute() = 0;
};

/**
 * 命令接收者
*/
class CompositeReceiver {
public:
    void ActionA() {
        printf("This is CompositeReceiver::ActionA()\n");
    }
    void ActionB() {
        printf("This is CompositeReceiver::ActionB()\n");
    }
};

/**
 * 具体命令
*/
class ConcreteCommandA : public AbstractMacroCommand {
public:
    ConcreteCommandA() {
        receiver_.reset(new CompositeReceiver());
    }
    void Execute() override {
        receiver_->ActionA();
    }
private:
    std::shared_ptr<CompositeReceiver> receiver_;
};

class ConcreteCommandB : public AbstractMacroCommand {
public:
    ConcreteCommandB() {
        receiver_.reset(new CompositeReceiver());
    }
    void Execute() override {
        receiver_->ActionB();
    }
private:
    std::shared_ptr<CompositeReceiver> receiver_;
};

/**
 * 命令请求
*/
class CompositeInvoker {
public:
    void AddCommand(AbstractMacroCommand* cmd) {
        cmds_.push_back(cmd);
    }

    void RemoveCommand(AbstractMacroCommand* cmd) {
        for (auto it = cmds_.begin(); it != cmds_.end(); it++) {
            if (cmd == *it) {
                cmds_.erase(it);
                break;
            }
        }
    }

    void Request() {
        for (auto cmd : cmds_) {
            cmd->Execute();
        }
    }
private:
    std::vector<AbstractMacroCommand*> cmds_; 
};

int main() {
    std::shared_ptr<AbstractMacroCommand> cmdA = std::make_shared<ConcreteCommandA>();
    std::shared_ptr<AbstractMacroCommand> cmdB = std::make_shared<ConcreteCommandB>();
    std::shared_ptr<AbstractMacroCommand> cmdA2 = std::make_shared<ConcreteCommandA>();

    CompositeInvoker client;
    client.AddCommand(cmdA.get());
    client.AddCommand(cmdB.get());
    client.AddCommand(cmdA2.get());
    client.Request();
    client.RemoveCommand(cmdA.get());
    client.Request();
    return 0;
}
