//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <string>
#include <vector>
#include <iostream>

class AbstractCustomer {
 public:
  virtual bool IsNil() = 0;
  virtual std::string GetName() = 0;
  virtual ~AbstractCustomer() = default;
 protected:
  std::string name_;
};

class RealCustomer: public AbstractCustomer {
 public:
  explicit RealCustomer(std::string name) {
    name_ = std::move(name);
  }
  std::string GetName() override {
    return name_;
  }
  bool IsNil() override {
    return false;
  }
};

class NullCustomer: public AbstractCustomer {
  std::string GetName() override {
    return "Not Available in Customer Database";
  }
  bool IsNil() override {
    return true;
  }
};

class CustomerFactory {
 public:
  static std::vector<std::string> names;
  static AbstractCustomer* GetCustomer(const std::string& name) {
    for (const auto & i : names) {
      if (i == name) {
        return new RealCustomer(name);
      }
    }
    return new NullCustomer();
  }
};

std::vector<std::string> CustomerFactory::names = {"Rob", "Joe", "Julie"};

int main() {
  AbstractCustomer* customer1 = CustomerFactory::GetCustomer("Rob");
  AbstractCustomer* customer2 = CustomerFactory::GetCustomer("Bob");
  AbstractCustomer* customer3 = CustomerFactory::GetCustomer("Julie");
  AbstractCustomer* customer4 = CustomerFactory::GetCustomer("Laura");
  std::cout << "Customers" << std::endl;
  std::cout << customer1->GetName() << std::endl;
  std::cout << customer2->GetName() << std::endl;
  std::cout << customer3->GetName() << std::endl;
  std::cout << customer4->GetName() << std::endl;
  delete customer1;
  delete customer2;
  delete customer3;
  delete customer4;
}
