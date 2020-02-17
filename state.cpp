//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <iostream>
#include <string>

class Context;
class State;

class Context {
 public:
  Context(){state_ = nullptr;}
  void SetSate(State* state){
    state_ = state;
  }
  State* GetState() {
    return state_;
  }
 private:
  State* state_;
};

class State {
 public:
  virtual void DoAction(Context* context) = 0;
  virtual std::string ToString() = 0;
  virtual ~State() = default;
};

class StartState: public State {
 public:
  void DoAction(Context *context) override {
    std::cout << "Player is in start state" << std::endl;
    context->SetSate(this);
  }
  std::string ToString() override {
    return "Start State";
  }
};

class StopState: public State {
 public:
  void DoAction(Context *context) override {
    std::cout << "Player is in stop state" << std::endl;
    context->SetSate(this);
  }
  std::string ToString() override {
    return "Stop State";
  }
};

int main() {
  Context* context = new Context();
  StartState start_state;
  start_state.DoAction(context);
  std::cout << context->GetState()->ToString() << std::endl;
  StopState stop_state;
  stop_state.DoAction(context);
  std::cout << context->GetState()->ToString() << std::endl;
  delete context;
}

