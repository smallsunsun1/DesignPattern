//
// Created by 孙嘉禾 on 2020/1/20.
//

#include <iostream>
#include <string>

class Shape{};
class Rectangle:public Shape{
  int h_;
  int w_;
};
class Circle: public Shape{
  int r_;
};

class Factory {
 public:
  static Shape* GetShape(const std::string& type) {
    if (type == "Circle")
      return new Circle();
    else if (type == "Rectangle")
      return new Rectangle();
    else
      return nullptr;
  }
};

int main() {
  auto a = Factory::GetShape("Circle");
  delete a;
}


