#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <vector>
#include <map>

using std::cout;
using std::endl;

/*
    用解释器模式设计一个"厦漳泉"公交车卡的读卡器程序。

    说明：假如"厦漳泉"公交车读卡器可以判断乘客的身份，如果是这三座城市的"老人"" "妇女" "儿童"就可以免费乘车，其他人员乘车一次扣 2 元。
*/
/*
    文法规则
    <expression> ::= <city>的<person>
    <city> ::= 厦门|泉州|漳州
    <person> ::= 老人|妇女|儿童
*/

class AbstractExpression {
public:
    virtual ~AbstractExpression() {}
    virtual bool Interpret(const std::string& info) = 0;
};

class TerminalExpression : public AbstractExpression {
public: 
    TerminalExpression(const std::vector<std::string>& content) : content_(content) {}

    bool Interpret(const std::string& info) override {
        for (auto& content : content_) {
            if (info == content) 
                return true;
            
            std::size_t len = info.size();
            for (int  i = 0; i < content.size(); i++) {
                if (i + len <= content.size() && content.substr(i, i+len).compare(info) == 0) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    std::vector<std::string> content_;
};

class NonterminalExpression : public AbstractExpression {
public:
    NonterminalExpression(std::shared_ptr<AbstractExpression>& city_eps, std::shared_ptr<AbstractExpression>& person_eps)
        : city_eps_(city_eps), person_eps_(person_eps) {}

    bool Interpret(const std::string& info) {
        std::vector<std::string> split_vec;
        if (Split(info, '|', split_vec) != 2) return false;
        return city_eps_->Interpret(split_vec[0]) && person_eps_->Interpret(split_vec[1]);
    }

protected:
    size_t Split(const std::string& src, char ch, std::vector<std::string>& vec) {
        size_t pos = 0;
        std::string tmp;
        for (size_t i = 0; i < src.size(); i++) {
            if (src[i] == ch) {
                tmp = src.substr(pos, i - pos);
                if (!tmp.empty() && tmp != "\n")
                    vec.push_back(tmp);
                pos = i + 1;
            }
        }
        if (pos <= src.size()) {
            tmp = src.substr(pos, src.size() - pos);
            if (!tmp.empty() && tmp != "\n")
                vec.push_back(tmp);
        }
        return vec.size();
    }

private: 
    std::shared_ptr<AbstractExpression> city_eps_ = nullptr;
    std::shared_ptr<AbstractExpression> person_eps_ = nullptr;
};

class Context {
public:
    Context() {
        std::vector<std::string> citys;
        std::vector<std::string> persons;

        citys.emplace_back("厦门");
        citys.emplace_back("漳州");
        citys.emplace_back("泉州");

        persons.emplace_back("老人");
        persons.emplace_back("妇女");
        persons.emplace_back("儿童");

        std::shared_ptr<AbstractExpression> city_eps = std::make_shared<TerminalExpression>(citys);
        std::shared_ptr<AbstractExpression> person_eps = std::make_shared<TerminalExpression>(persons);

        eps_ = std::make_shared<NonterminalExpression>(city_eps, person_eps);
    }

    void FreeRide(const std::string& info) {
        if (eps_ && eps_->Interpret(info)) {
            printf("身份识别: %s, 本次乘车免费\n", info.c_str());
        } else {
            printf("身份识别: %s, 本次乘车扣费 2 元\n", info.c_str());
        }
    }
protected:
    std::shared_ptr<AbstractExpression> eps_;
};
int main() {

    std::shared_ptr<Context> context = std::make_shared<Context>();
    context->FreeRide("厦门|老人");
    context->FreeRide("漳州|妇女");
    context->FreeRide("泉州|儿童");
    context->FreeRide("上海|老人");
    context->FreeRide("厦门|青年");
    return 0;
}
