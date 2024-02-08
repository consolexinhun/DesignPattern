#include <iostream>
#include <memory>
#include <string>
#include <cstdio>

using std::cout;
using std::endl;

class Game {
public:
    virtual ~Game() = default;
    virtual void Play() = 0;
};

class GameA : public Game {
public:
    void Play() override {
        puts("Playing GameA");
    }
};
class GameB : public Game {
public:
    void Play() override {
        puts("Playing GameB");
    }
};

class Phone {
public:
    Phone(const std::shared_ptr<Game>& game) {
        game_ = game;
    }
    virtual ~Phone() = default;
    virtual void Play() = 0;

protected:
    std::shared_ptr<Game> game_;
};

class PhoneA : public Phone {
public:
    PhoneA(const std::shared_ptr<Game>& game) : Phone(game) {}
    void Play() override {
        puts("PhoneA");
        game_->Play();
    }
};

class PhoneB : public Phone {
public:
    PhoneB(const std::shared_ptr<Game>& game) : Phone(game) {}
    void Play() override {
        puts("PhoneB");
        game_->Play();
    }
};


int main() {
    std::shared_ptr<Game> game = std::make_shared<GameA>();
    std::shared_ptr<Phone> phone = std::make_shared<PhoneA>(game);
    phone->Play();  // 用 A 手机玩游戏 A

    game.reset(new GameB());
    phone.reset(new PhoneA(game));
    phone->Play();  // 用 A 手机玩游戏 B
    return 0;
}
