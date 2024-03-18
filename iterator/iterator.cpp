#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>
#include <map>

using std::cout;
using std::endl;

template<typename T, typename U>
class Iterator {
public:
    using iter_type = typename std::vector<T>::iterator;

    Iterator(U* data, bool reverse = false) : data_(data) {
        it_ = data_->m_data_.begin();
    }

    void First() {
        it_ = data_->m_data_.begin();
    }
    void Next() {
        it_++;
    }

    bool IsEnd() {
        return it_ == data_->m_data_.end();
    }

    iter_type Current() {
        return it_;
    }
private:
    U* data_;
    iter_type it_;
};

template<typename T>
class Container {
    friend class Iterator<T, Container>;
public:
    void Add(T a) {
        m_data_.push_back(a);
    }

    std::shared_ptr<Iterator<T, Container>> CreateIterator() {
        return std::make_shared<Iterator<T, Container>>(this);
    }

private:
    std::vector<T> m_data_;
};

class Data {
public:
    Data(int a = 0) : m_data_(a) {}

    void SetData(int a) {
        m_data_ = a;
    }
    int GetData() {
        return m_data_;
    }
private:
    int m_data_;
};

int main() {
    Container<int> cnt;
    for (int i = 0; i < 10; i++) {
        cnt.Add(i);
    }

    std::shared_ptr<Iterator<int, Container<int>>> it = cnt.CreateIterator();
    for (it->First(); !it->IsEnd(); it->Next()) {
        std::cout << *(it->Current()) << std::endl;
    }

    Container<Data> cnt2;
    Data a(10), b(100), c(1000);
    cnt2.Add(a);
    cnt2.Add(b);
    cnt2.Add(c);

    std::shared_ptr<Iterator<Data, Container<Data>>> it2 = cnt2.CreateIterator();
    for (it2->First(); !it2->IsEnd(); it2->Next()) {
        std::cout << it2->Current()->GetData() << std::endl;
    }
    return 0;
}
