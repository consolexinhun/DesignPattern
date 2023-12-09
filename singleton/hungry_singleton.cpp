class HungrySingleton {
private:
    HungrySingleton() {}

public:
    static HungrySingleton* GetInstance() {
        return instance_;
    }

private:
    static HungrySingleton* instance_;
};

HungrySingleton* HungrySingleton::instance_ = new HungrySingleton();

int main() {
    HungrySingleton* instance = HungrySingleton::GetInstance();
    return 0;
}

