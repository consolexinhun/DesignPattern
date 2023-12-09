class MySingleton {
private:
    MySingleton() {}

public:
    static MySingleton& GetInstance() {
        static MySingleton instance;
        return instance;
    }
};

int main() {
    MySingleton& instance = MySingleton::GetInstance();
    return 0;
}
