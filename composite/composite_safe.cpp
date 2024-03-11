#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>
#include <map>

using std::cout;
using std::endl;

/**
 * 安全组合模式：
 * 优点：将管理子构件的方法移到了树枝构件中，抽象构件和树叶构建没有子对象的管理
 * 缺点：叶子和分支有不同的接口，客户端在调用时需要知道树叶对象和树枝对象的存在
*/

/**
 * 抽象构件
*/
class AbstractSafeComponent {
public:
    virtual ~AbstractSafeComponent() {}
    virtual void Operation() = 0;
};

/**
 * 树叶构件
*/
class LeafSafeComponent : public AbstractSafeComponent {
public:
    LeafSafeComponent(const std::string& name) : name_(name) {}
    void Operation() override { 
        printf("This(%s) is LeafSafeComponent::Operation()!\n", name_.c_str());
    } 

private:
    std::string name_;
};

/**
 * 树枝构建
*/
class CompositeSafeComponent : public AbstractSafeComponent {
public:
    void Add(AbstractSafeComponent* comp) {
        children_.push_back(comp);
    }
    void Remove(AbstractSafeComponent* comp) {
        for (auto it = children_.begin(); it != children_.end(); it++) {
            if (*it == comp) {
                children_.erase(it++);
                break;
            }
        }
    }
    AbstractSafeComponent* GetChild(int id) {
        if (id > 0 && id < children_.size()) return children_[id];
        return nullptr;
    }

    void Operation() override {
        for (AbstractSafeComponent* child : children_) {
            child->Operation();
        }
    }
private:
    std::vector<AbstractSafeComponent*> children_;
};

int main() {
    std::shared_ptr<AbstractSafeComponent> composite = std::make_shared<CompositeSafeComponent>();

    std::unique_ptr<AbstractSafeComponent> leafA = std::make_unique<LeafSafeComponent>("Leaf A");
    std::unique_ptr<AbstractSafeComponent> leafB = std::make_unique<LeafSafeComponent>("Leaf B");
    std::unique_ptr<AbstractSafeComponent> leafC = std::make_unique<LeafSafeComponent>("Leaf C");

    {
        std::shared_ptr<CompositeSafeComponent> ptr = std::dynamic_pointer_cast<CompositeSafeComponent>(composite);
        ptr->Add(leafA.get());
        ptr->Add(leafB.get());
        ptr->Add(leafC.get());

        AbstractSafeComponent* tmp = ptr->GetChild(1);
        tmp->Operation();
        ptr->Remove(tmp);
    }

    composite->Operation();
    return 0;
}
