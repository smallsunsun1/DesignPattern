//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <string>
#include <regex>
#include <iostream>

class Expression {
 public:
  virtual bool Interpret(const std::string &context) = 0;
  virtual ~Expression() = default;
};

class TerminalExpression : public Expression {
 public:
  explicit TerminalExpression(std::string data) : data_(std::move(data)) {}
  bool Interpret(const std::string &context) override {
    std::regex re(data_);
    return std::regex_search(context.begin(), context.end(), re);
  }
 private:
  std::string data_;
};

class OrExpression : public Expression {
 public:
  explicit OrExpression(Expression *expr1, Expression *expr2) : expr1_(expr1), expr2_(expr2) {

  }
  bool Interpret(const std::string &context) override {
    return expr1_->Interpret(context) || expr2_->Interpret(context);
  }
 private:
  Expression *expr1_ = nullptr;
  Expression *expr2_ = nullptr;
};

class AndExpression : public Expression {
 public:
  explicit AndExpression(Expression *expr1, Expression *expr2) : expr1_(expr1), expr2_(expr2) {

  }
  bool Interpret(const std::string &context) override {
    return expr1_->Interpret(context) && expr2_->Interpret(context);
  }
 private:
  Expression *expr1_ = nullptr;
  Expression *expr2_ = nullptr;
};


int main() {
  Expression* robert = new TerminalExpression("Robert");
  Expression* john = new TerminalExpression("John");
  Expression* or_expression = new OrExpression(robert, john);
  Expression* julie = new TerminalExpression("Julie");
  Expression* married = new TerminalExpression("Married");
  Expression* and_expression = new AndExpression(julie, married);
  std::cout << "John is male ? : " << or_expression->Interpret("john") << std::endl;
  std::cout << "Julie is a married women? : " << and_expression->Interpret("Married Julie") << std::endl;
  delete robert;
  delete john;
  delete or_expression;
  delete julie;
  delete married;
  delete and_expression;
}

