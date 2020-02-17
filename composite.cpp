//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <string>
#include <list>

class Emplyee {
 public:
  Emplyee(const std::string &name, const std::string &dept, int sal) : name_(name), dept_(dept), salary_(sal) {

  }
  void Add(Emplyee* e) {
      subordinates_.push_back(e);
  }
  void Remove(Emplyee* e) {
      subordinates_.remove(e);
  }
  std::list<Emplyee*> &getSubordinates() {
      return subordinates_;
  }
  std::string toString() {
      return "Emplyee : [ Name :" + name_ + ", dept : " + dept_ + ", salary :" + std::to_string(salary_) + " ]";
  }
 private:
  std::string name_;
  std::string dept_;
  int salary_;
  std::list<Emplyee*> subordinates_;
};

int main() {
    Emplyee* CEO = new Emplyee("john", "CEO", 30000);
    Emplyee* headSales = new Emplyee("Robert", "Head Sales", 20000);
    Emplyee* headMarketing = new Emplyee("Michel", "Head Marketing", 20000);
    Emplyee* clerk1 = new Emplyee("Laura", "Marketing", 10000);
    Emplyee* clerk2 = new Emplyee("Bob", "Marketing", 10000);
    Emplyee* salesExecutive1 = new Emplyee("Richard", "Sales", 10000);
    Emplyee* salesExecutive2 = new Emplyee("Rob", "sales", 10000);
    CEO->Add(headSales);
    CEO->Add(headMarketing);
    headSales->Add(salesExecutive1);
    headSales->Add(salesExecutive2);
    headMarketing->Add(clerk1);
    headMarketing->Add(clerk2);
    delete CEO;
    delete headSales;
    delete headMarketing;
    delete clerk1;
    delete clerk2;
    delete salesExecutive1;
    delete salesExecutive2;
    return 0;
}
