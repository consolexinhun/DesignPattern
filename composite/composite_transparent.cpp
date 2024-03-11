#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>

using std::cout;
using std::endl;

/**
 * 透明组合模式：
 * 优点：声明了子类中全部的方法
 * 缺点：没有的方法必须要实现
*/

/**
 * 透明组合模式：声明访问和管理子类的接口
*/
class AbstractTransparentComponent {
public:
    virtual ~AbstractTransparentComponent() {}

    /**
     * 透明组合模式需要声明子类下的全部方法
    */
    virtual void Add(AbstractTransparentComponent* comp) = 0;
    virtual void Remove(AbstractTransparentComponent* comp) = 0;
    virtual AbstractTransparentComponent* GetChild(int id) = 0;

    virtual void Operation() = 0;
};

/**
 * 树叶组合结构
*/

class LeafTransparentComponent : public AbstractTransparentComponent {
public:
    LeafTransparentComponent(const std::string& name) : name_(name) {}

    // 透明组合模式下，树叶结构需要实现不必要的接口
    void Add(AbstractTransparentComponent* comp) override {
        puts("Error! Leaf can't realize Add()!");
    }
    void Remove(AbstractTransparentComponent* comp) override {
        puts("Error! Leaf can't realize Remove()!");
    }
    AbstractTransparentComponent* GetChild(int id) override {
        puts("Error! Leaf can't realize GetChild()!");
        return nullptr;
    }

    void Operation() override {
        printf("This(%s) is LeafTranspatentComponent::Operation()!\n", name_.c_str());
    }

private:
    std::string name_;
};

/**
 * 树枝组合结构：管理和存储子部件
*/
class CompositeTransparentComponent : public AbstractTransparentComponent {
public:
    void Add(AbstractTransparentComponent* comp) override {
        children_.push_back(comp);
    }

    void Remove(AbstractTransparentComponent* comp) override {
        for (auto it = children_.begin(); it != children_.end(); it++) {
            if (*it == comp) {
                children_.erase(it++);
                break;
            }
        }
    }

    AbstractTransparentComponent* GetChild(int id) override {
        if (id > 0 && id < children_.size()) return children_[id];
        return nullptr;
    }

    void Operation() override {
        for (AbstractTransparentComponent* child : children_) {
            child->Operation();
        }
    }

private:
    std::vector<AbstractTransparentComponent*> children_;
};

int main() {

    std::unique_ptr<AbstractTransparentComponent> composite = std::make_unique<CompositeTransparentComponent>();

    std::unique_ptr<AbstractTransparentComponent> leafA = std::make_unique<LeafTransparentComponent>("Leaf A");
    std::unique_ptr<AbstractTransparentComponent> leafB = std::make_unique<LeafTransparentComponent>("Leaf B");
    std::unique_ptr<AbstractTransparentComponent> leafC = std::make_unique<LeafTransparentComponent>("Leaf C");

    composite->Add(leafA.get());
    composite->Add(leafB.get());
    composite->Add(leafC.get());

    AbstractTransparentComponent* tmp = composite->GetChild(1);
    tmp->Operation();
    composite->Remove(tmp);

    composite->Operation();

    return 0;
}
