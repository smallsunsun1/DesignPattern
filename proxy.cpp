//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <string>
#include <utility>
#include <iostream>

class Image {
 public:
  virtual void Display() = 0;
  virtual ~Image() = default;
};

class RealImage : public Image {
 public:
  explicit RealImage(std::string filename) : filename_(std::move(filename)) {
    LoadFromDisk(filename_);
  }
  void Display() override {
    std::cout << "Displaying" + filename_ << std::endl;
  }
 private:
  static void LoadFromDisk(const std::string& filename) {
    std::cout << "Loading " + filename << std::endl;
  }
  std::string filename_;
};

class ProxyImage: public Image {
 public:
  explicit ProxyImage(std::string filename):filename_(std::move(filename)){
    realimage_ = new RealImage(filename_);
  }
  void Display() override {
    if (realimage_ == nullptr) {
      realimage_ = new RealImage(filename_);
    }
    realimage_->Display();
  }
  ~ProxyImage() override {
    delete realimage_;
  }
 private:
  RealImage* realimage_;
  std::string filename_;
};

int main() {
  Image* image = new ProxyImage("test_10mb.jpg");
  image->Display();
  delete image;
}

