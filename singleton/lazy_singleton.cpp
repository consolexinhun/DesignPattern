#include <mutex>
#include <thread>

class LazySingleton {
private:
    LazySingleton() {}

public:
    static LazySingleton* GetInstance() {
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
std::mutex LazySingleton::mutex_;

int main() {
    LazySingleton* instance = LazySingleton::GetInstance();
    return 0;
}
