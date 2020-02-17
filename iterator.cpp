//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <iostream>
#include <vector>

template<typename T>
class Iterator {
 public:
  virtual bool HasNext() = 0;
  virtual ~Iterator() = default;
  virtual T GetNext() = 0;
};

template<typename T>
class Container {
 public:
  virtual Iterator<T>* GetIterator() = 0;
  virtual ~Container() = default;
};

template<typename T>
class NameRepository : public Container<T> {
 public:
  Iterator<T>* GetIterator() override {
    return new NameIterator();
  }
  static std::vector<T> names_;
  static void AddName(const std::string& name) {
    names_.push_back(name);
  }
 private:
  class NameIterator : public Iterator<T> {
   public:
    NameIterator() {
      index_ = 0;
    }
    bool HasNext() override {
      return index_ < names_.size();
    }
    T GetNext() override {
      if (HasNext()) {
        return names_[index_++];
      } else {
        return T{};
      }
    }
   private:
    int index_;
  };
};

template <typename T>
std::vector<T> NameRepository<T>::names_ = std::vector<T> {};

int main() {
  NameRepository<std::string> name_repository;
  for (int i = 0; i < 10; ++i) {
    NameRepository<std::string>::AddName(std::to_string(i));
  }
  for (auto iter = name_repository.GetIterator(); iter->HasNext();) {
    std::string name = iter->GetNext();
    std::cout << "Name : " + name << std::endl;
  }
}
