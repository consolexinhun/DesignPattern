class HungrySingleton {
private:
    HungrySingleton() {}

public:
    HungrySingleton* GetInstance() {
        return instance_;
    }

private:
    HungrySingleton() {}

    static HungrySingleton* instance_;
};

HungrySingleton* HungrySingleton::instance_ = new HungrySingleton();

