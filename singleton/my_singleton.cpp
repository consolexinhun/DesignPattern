class MySingleton {
private:
    MySingleton() {}

public:
    static MySingleton& GetInstance() {
        static MySingleton instance;
        return instance;
    }
};
