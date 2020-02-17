//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <string>
#include <iostream>

class ChatRoom;
class User;

class ChatRoom{
 public:
  static void ShowMessage(User* user, const std::string& message);
};

class User {
 public:
  std::string GetName() {
    return name_;
  }
  void SetName(const std::string& name){
    name_ = name;
  }
  explicit User(std::string name):name_(std::move(name)){}
  void SendMessage(const std::string& message) {
    ChatRoom::ShowMessage(this, message);
  }
 private:
  std::string name_;
};

void ChatRoom::ShowMessage(User *user, const std::string &message) {
  std::cout << " [" + user->GetName() + "] : " + message;
}

int main() {
  User robert("Robert");
  User john("john");
  robert.SendMessage("Hi! John!");
  john.SendMessage("Hello! Robert!");
}