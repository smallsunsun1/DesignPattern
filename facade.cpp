//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <iostream>

class Shape {
 public:
  virtual void Draw() = 0;
  virtual ~Shape() {}
};

class Rectangle : public Shape {
 public:
  void Draw() override {
      std::cout << "Rectangle::draw()" << std::endl;
  }
};

class Square : public Shape {
 public:
  void Draw() override {
      std::cout << "Square::draw()" << std::endl;
  }
};

class Circle : public Shape {
 public:
  void Draw() override {
      std::cout << "Circle::draw()" << std::endl;
  }
};

//接下去实现一个外观类
class ShapeMaker {
 public:
  ShapeMaker() {
      circle_ = new Circle();
      rectangle_ = new Rectangle();
      square_ = new Square();
  }
  ~ShapeMaker() {
      delete circle_;
      delete rectangle_;
      delete square_;
  }
  void DrawCircle() {
      circle_->Draw();
  }
  void DrawRectangle() {
      rectangle_->Draw();
  }
  void DrawSquare() {
      square_->Draw();
  }
 private:
  Shape *circle_;
  Shape *rectangle_;
  Shape *square_;
};

int main() {
    ShapeMaker shapeMaker;
    shapeMaker.DrawCircle();
    shapeMaker.DrawRectangle();
    shapeMaker.DrawSquare();
    return 0;
}
