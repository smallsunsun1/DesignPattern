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
      std::cout << "Shape: Rectangle" << std::endl;
  }
};

class Circle : public Shape {
 public:
  void Draw() override {
      std::cout << "Shape: Circle" << std::endl;
  }
};

class ShapeDecorator : public Shape {
 public:
  ShapeDecorator(Shape *decoratedShape) : decoratedShape_(decoratedShape) {

  }
  virtual void Draw() override {
      decoratedShape_->Draw();
  }
 protected:
  Shape *decoratedShape_;
};

class RedShapeDecotrator : public ShapeDecorator {
 public:
  RedShapeDecotrator(Shape *decoratedShape) : ShapeDecorator(decoratedShape) {

  }
  void Draw() override {
      decoratedShape_->Draw();
      SetRedBorder(decoratedShape_);
  }
 private:
  void SetRedBorder(Shape* decoratedShape) {
      std::cout << "Border Color: Red" << std::endl;
  }
};

int main() {
    Shape* circle = new Circle();
    Shape* rectangle = new Rectangle();
    ShapeDecorator* redCircle = new RedShapeDecotrator(circle);
    ShapeDecorator* redRectangle = new RedShapeDecotrator(rectangle);
    circle->Draw();
    rectangle->Draw();
    redCircle->Draw();
    redRectangle->Draw();
    delete circle;
    delete rectangle;
    delete redCircle;
    delete redRectangle;
}
