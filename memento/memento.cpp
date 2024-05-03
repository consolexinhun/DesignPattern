#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>
#include <map>

using std::cout;
using std::endl;

// 备忘录
class Memento {
public:
    Memento(const std::string& name) : name_(name) {}
    const std::string& GetName() const {
        return name_;
    }

private:
    std::string name_;
};

// 发起人，记录当前内部状态
class Originator {
public:
    void SetName(const std::string& name) {
        name_ = name;
    }
    const std::string& GetName() const {
        return name_;
    }

    std::shared_ptr<Memento> CreateMemento() {
        return std::make_shared<Memento>(name_);
    }

    void RestoreMemento(std::shared_ptr<Memento> m) {
        SetName(m->GetName());
    }

private:
    std::string name_;
};


// 管理者
class Caretaker {
public:
    ~Caretaker() {}

    void Push(std::shared_ptr<Memento> people) {
        peoples.emplace_back(people);
    }

    std::shared_ptr<Memento> Pop() {
        std::shared_ptr<Memento> people = peoples.back();
        peoples.pop_back();
        return people;
    }
private:
    std::vector<std::shared_ptr<Memento>> peoples;
};

int main() {
    std::shared_ptr<Originator> originator = std::make_shared<Originator>();
    std::shared_ptr<Caretaker> caretaker = std::make_shared<Caretaker>();
    originator->SetName("Alpha");
    caretaker->Push(originator->CreateMemento());
    printf("Now, You select : %s\n", originator->GetName().c_str());

    originator->SetName("Beta");
    printf("Now, you reselect: %s\n", originator->GetName().c_str());

    originator->RestoreMemento(caretaker->Pop());
    printf("Now, you restore to select: %s\n", originator->GetName().c_str());
    return 0;
}
