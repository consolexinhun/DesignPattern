#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>
#include <list>
#include <map>

using std::cout;
using std::endl;

class ConcreteElementA;
class ConcreteElementB;

/**
 * 抽象访问者，定义访问具体元素的接口
*/
class AbstractVisitor {
public:
    virtual ~AbstractVisitor() {}

    virtual void Visit(ConcreteElementA* element) = 0;
    virtual void Visit(ConcreteElementB* element) = 0;
};


class ConcreteVisitorA : public AbstractVisitor {
public:
    void Visit(ConcreteElementA* element) override;
    void Visit(ConcreteElementB* element) override;
};

class ConcreteVisitorB : public AbstractVisitor {
public:
    void Visit(ConcreteElementA* element) override;
    void Visit(ConcreteElementB* element) override;
};

/**
 * 抽象元素，声明包含接受操作的接口
*/
class AbstractElement {
public:
    virtual ~AbstractElement() {}
    virtual void Accept(AbstractVisitor* visitor) = 0;
};

class ConcreteElementA : public AbstractElement {
public:
    void Accept(AbstractVisitor* visitor) override {
        visitor->Visit(this);
    }

    void OperatorA() {
        printf("This is ConcreteElementA::OperatorA\n");
    }
};

class ConcreteElementB : public AbstractElement {
public:
    void Accept(AbstractVisitor* visitor) override {
        visitor->Visit(this);
    }

    void OperatorB() {
        printf("This is ConcreteElementB::OperatorB\n");
    }
};

void ConcreteVisitorA::Visit(ConcreteElementA* element) {
    printf("This is ConcreteVisitorA::Visit\n");
    element->OperatorA();
}
void ConcreteVisitorA::Visit(ConcreteElementB* element) {
    printf("This is ConcreteVisitorA::Visit\n");
    element->OperatorB();
}

void ConcreteVisitorB::Visit(ConcreteElementA* element) {
    printf("This is ConcreteVisitorB::Visit\n");
    element->OperatorA();
}
void ConcreteVisitorB::Visit(ConcreteElementB* element) {
    printf("This is ConcreteVisitorB::Visit\n");
    element->OperatorB();
}

int main() {
    // std::shared_ptr<AbstractElement>
    std::list<std::shared_ptr<AbstractElement>> elements;
    elements.emplace_back(new ConcreteElementA());
    elements.emplace_back(new ConcreteElementB());

    std::shared_ptr<AbstractVisitor> visitorA = std::make_shared<ConcreteVisitorA>();
    for (auto& e : elements) {
        e->Accept(visitorA.get());
    }


    std::shared_ptr<AbstractVisitor> visitorB = std::make_shared<ConcreteVisitorB>();
    for (auto& e : elements) {
        e->Accept(visitorB.get());
    }
    return 0;
}
