#include <mutex>

class LazySingleton {
private:
    LazySingleton() {}

public:
    LazySingleton* GetInstance() {
        if (!instance_) {
            std::unique_lock<std::mutex> lock(mutex_);
            if (!instance_) instance_ = new LazySingleton();
        }
        return instance_;
    }

private:
    static LazySingleton* instance_;
    static std::mutex mutex_;
};

LazySingleton* LazySingleton::instance_ = nullptr;
