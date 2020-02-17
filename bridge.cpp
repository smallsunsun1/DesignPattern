//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <iostream>

class DrawAPI {
 public:
  virtual void drawCircle(int radius, int x, int y) = 0;
};

class RedCircle : public DrawAPI {
 public:
  void drawCircle(int radius, int x, int y) {
      std::cout << "Drawing Circle [color: red, radius: ]" << radius << ", x: " << x << ", y:" << y
                << "]" << std::endl;
  }
};

class GreenCircle : public DrawAPI {
 public:
  void drawCircle(int radius, int x, int y) override {
      std::cout << "Draw Green Circle" << std::endl;
  }
};

class Shape {
 public:
  virtual void draw() = 0;
 protected:
  DrawAPI *drawApi_;
  Shape(DrawAPI *drawApi) {
      drawApi_ = drawApi;
  }
};

class Circle : public Shape {
 public:
  Circle(int x, int y, int radius, DrawAPI *drawApi) : Shape(drawApi) {
      x_ = x;
      y_ = y;
      radius_ = radius;
  }
  void draw() override {
      drawApi_->drawCircle(radius_, x_, y_);
  }
 private:
  int x_;
  int y_;
  int radius_;
};

int main() {
    RedCircle* p1;
    {
        auto redCircle = std::make_unique<RedCircle>();
        auto greenCircle = std::make_unique<GreenCircle>();
        Circle c1(100, 100, 10, redCircle.get());
        Circle c2(100, 100, 10, greenCircle.get());
        c1.draw();
        c2.draw();
        p1 = redCircle.get();
    }
    return 0;
}
