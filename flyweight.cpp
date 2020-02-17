//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

class Shape {
 public:
  virtual void Draw() = 0;
  virtual ~Shape() = default;
};

class Circle : public Shape {
 public:
  explicit Circle(std::string color) : color_(std::move(color)) {}
  void setX(int x) { x_ = x; }
  void setY(int y) { y_ = y; }
  void SetRadius(int radius) { radius_ = radius; }
  void Draw() override {
    std::cout << "Circle: Draw() [Color : " + color_ + ", x : " + std::to_string(x_)
        + ", y :" + std::to_string(y_) + ", radius :" + std::to_string(radius_) << std::endl;
  }

 private:
  int x_;
  int y_;
  int radius_;
  std::string color_;
};

class ShapeFactory {
 public:
  static Shape* GetCircle(const std::string& color) {
    auto iter = circleMap.find(color);
    Shape* circle;
    if (iter == circleMap.end()) {
      circle = new Circle(color);
      circleMap.try_emplace(color, circle);
      std::cout << "Creating circle of color: " + color << std::endl;
    } else{
      circle = iter->second;
    }
    return circle;
  }
 private:
  static std::unordered_map<std::string, Shape *> circleMap;
};

std::unordered_map<std::string, Shape *> ShapeFactory::circleMap = std::unordered_map<std::string, Shape *>{};

int main() {
  std::vector<std::string> colors = {"Red", "Green", "Blue", "White", "Black"};
  for (int i = 0; i < 20; ++i) {
    int val = std::rand() % 5;
    int randx = std::rand();
    int randy = std::rand();
    Circle* circle = dynamic_cast<Circle*>(ShapeFactory::GetCircle(colors[val]));
    circle->setX(randx);
    circle->setY(randy);
    circle->SetRadius(100);
    circle->Draw();
  }
}

