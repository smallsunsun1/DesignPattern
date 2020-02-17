//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <list>
#include <string>
#include <iostream>

class Subject;

class Observer {
 public:
  virtual void Update() = 0;
  virtual ~Observer() = default;
 protected:
  Subject *subject_ = nullptr;
};

class Subject {
 public:
  int GetState() {
    return state_;
  }
  void SetState(int state) {
    state_ = state;
    NotifyAllObservers();
  }
  void Attach(Observer *observer) {
    observers_.push_front(observer);
  }
  void NotifyAllObservers() {
    for (auto observer: observers_) {
      observer->Update();
    }
  }
 private:
  std::list<Observer *> observers_;
  int state_;
};

class BinaryObserver : public Observer {
 public:
  explicit BinaryObserver(Subject *subject) {
    subject_ = subject;
    subject_->Attach(this);
  }
  void Update() override {
    std::cout << "Binary String: " + std::to_string(subject_->GetState()) << std::endl;
  }
};

class OctalObserver : public Observer {
 public:
  explicit OctalObserver(Subject *subject) {
    subject_ = subject;
    subject_->Attach(this);
  }
  void Update() override {
    std::cout << "Octal String: " + std::to_string(subject_->GetState()) << std::endl;
  }
};

class HexaObserver : public Observer {
 public:
  explicit HexaObserver(Subject *subject) {
    subject_ = subject;
    subject_->Attach(this);
  }
  void Update() override {
    std::cout << "Hex String: " + std::to_string(subject_->GetState()) << std::endl;
  }
};

int main() {
  auto subject = new Subject();
  auto hex_observer = new HexaObserver(subject);
  auto oct_observer = new OctalObserver(subject);
  auto bi_observer = new BinaryObserver(subject);
  subject->SetState(15);
  subject->SetState(10);
  delete subject;
  delete hex_observer;
  delete oct_observer;
  delete bi_observer;
}
