//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <string>
#include <iostream>

class Strategy {
 public:
  virtual int DoOperation(int num1, int num2) = 0;
  virtual ~Strategy() = default;
};

class OperationAdd: public Strategy {
 public:
  int DoOperation(int num1, int num2) override {
    return num1 + num2;
  }
};

class OperationSubstrct: public Strategy {
 public:
  int DoOperation(int num1, int num2) override {
    return num1 - num2;
  }
};

class OperationMultiply: public Strategy {
 public:
  int DoOperation(int num1, int num2) override {
    return num1 * num2;
  }
};

class Context {
 public:
  explicit Context(Strategy* strategy):strategy_(strategy){}
  void SetStrategy(Strategy* strategy) {
    strategy_ = strategy;
  }
  int ExecuteStratefy(int num1, int num2) {
    return strategy_->DoOperation(num1, num2);
  }
 private:
  Strategy* strategy_;
};

int main() {
  Strategy* add_op = new OperationAdd();
  Strategy* sub_op = new OperationSubstrct();
  Strategy* mul_op = new OperationMultiply();
  Context context(add_op);
  std::cout << context.ExecuteStratefy(1, 1) << std::endl;
  context.SetStrategy(sub_op);
  std::cout << context.ExecuteStratefy(1, 2) << std::endl;
  context.SetStrategy(mul_op);
  std::cout << context.ExecuteStratefy(1, 2) << std::endl;
  delete add_op;
  delete sub_op;
  delete mul_op;
}

