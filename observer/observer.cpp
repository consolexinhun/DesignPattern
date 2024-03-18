#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>
#include <map>

using std::cout;
using std::endl;

/**
 * 抽象观察者，包含更新自己的抽象方法，当收到具体主题的更改通知时被调用
*/
class AbstractObserver {
public:
    virtual ~AbstractObserver() {}
    virtual void Response() = 0;
};


class ConcreteObserverA : public AbstractObserver {
public:
    void Response() override {
        printf("This is ConcreteObserverA::Resonse()\n");
    }
};
class ConcreteObserverB : public AbstractObserver {
public:
    void Response() override {
        printf("This is COncreteObserverB::Response()\n");
    }
};

/**
 * 抽象主题，保存所有观察者对象，增加和删除观察者的方法，以及通知所有观察者的抽象方法
*/
class AbstractSubject {
public:
    virtual ~AbstractSubject() {}
    virtual void NotifyObserver() = 0;

    void AddObserver(AbstractObserver* observer) {
        observers_.emplace_back(observer);
    }
    void RemoveObserver(AbstractObserver* observer) {
        for (auto it = observers_.begin(); it != observers_.end(); it++) {
            if (*it == observer) {
                observers_.erase(it);
                break;
            }
        }
    }
protected:
    std::vector<AbstractObserver*> observers_; 
};

class ConcreteSubject : public AbstractSubject {
public:
    void NotifyObserver() override {
        for (auto observer : observers_) {
            observer->Response();
        }
    }
};
int main() {
    std::shared_ptr<AbstractSubject> subject = std::make_shared<ConcreteSubject>();

    std::shared_ptr<AbstractObserver> observerA = std::make_shared<ConcreteObserverA>();
    std::shared_ptr<AbstractObserver> observerB = std::make_shared<ConcreteObserverB>();

    subject->AddObserver(observerA.get());
    subject->AddObserver(observerB.get());

    subject->NotifyObserver();
    return 0;
}
