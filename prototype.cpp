//
// Created by 孙嘉禾 on 2020/1/20.
//

#include <string>
#include <iostream>
#include <unordered_map>

class Shape {
 public:
  virtual void Draw() = 0;
  std::string GetId() { return id_; }
  void SetId(const std::string &id) { id_ = id; }
  virtual Shape *Clone() = 0;
 protected:
  std::string type_;
 private:
  std::string id_ = "default";
};

class Rectangle : public Shape {
 public:
  Rectangle() { type_ = "Rectangle"; }
  void Draw() override {
    std::cout << "Inside Rectangle::Draw() method." << std::endl;
  }
  Shape * Clone() override {
    Shape* res = new Rectangle();
    return res;
  }
};

class Circle: public Shape {
 public:
  Circle() {type_ = "Circle";}
  void Draw() override {
    std::cout << "Inside Circle::Draw() method." << std::endl;
  }
  Shape * Clone() override {
    Shape* res = new Circle();
    return res;
  }
};

class ShapeCache {
 public:
  static Shape* Getshape(std::string shapeId) {
    Shape* cachedShape = shape_map[shapeId];
    return cachedShape->Clone();
  }
  static void LoadCache() {
    Circle* circle = new Circle();
    circle->SetId("1");
    shape_map[circle->GetId()] = circle;
    Rectangle* rectangle = new Rectangle();
    rectangle->SetId("2");
    shape_map[rectangle->GetId()] = rectangle;
  }
 private:
  static std::unordered_map<std::string, Shape*> shape_map;
};

std::unordered_map<std::string, Shape*> ShapeCache::shape_map = {};

int main() {
  ShapeCache::LoadCache();
  Shape* cloned_shape1 = ShapeCache::Getshape("1");
  Shape* cloned_shape2 = ShapeCache::Getshape("1");
  std::cout << cloned_shape1->GetId() << std::endl;
  std::cout << cloned_shape2->GetId() << std::endl;
}
