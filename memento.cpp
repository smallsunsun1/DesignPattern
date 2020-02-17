//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <string>
#include <vector>
#include <iostream>

class Memento {
 public:
  explicit Memento(std::string state) : state_(std::move(state)) {

  }
  [[nodiscard]] std::string GetState() const { return state_; }
 private:
  std::string state_;
};

class Originator {
 public:
  void SetState(const std::string &state) { state_ = state; }
  std::string GetState() {return state_;}
  Memento SaveStateToMemento() {
    return Memento(state_);
  }
  void GetStateFromMemento(const Memento& memento){
    state_ = memento.GetState();
  }
 private:
  std::string state_;
};

class CareTaker {
 public:
  void Add(const Memento& state) {
    memento_list_.push_back(state);
  }
  Memento Get(int index) {
    return memento_list_[index];
  }
 private:
  std::vector<Memento> memento_list_;
};

int main() {
  Originator originator;
  CareTaker care_taker;
  originator.SetState("State #1");
  originator.SetState("State #2");
  care_taker.Add(originator.SaveStateToMemento());
  originator.SetState("State #3");
  care_taker.Add(originator.SaveStateToMemento());
  originator.SetState("State #4");
  std::cout << "Current State: " + originator.GetState() << std::endl;
  originator.GetStateFromMemento(care_taker.Get(0));
  std::cout << "First saved State: " << originator.GetState() << std::endl;
  originator.GetStateFromMemento(care_taker.Get(1));
  std::cout << "Second saved State: " << originator.GetState() << std::endl;
}

