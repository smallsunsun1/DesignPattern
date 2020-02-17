//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <iostream>
#include <list>
#include <utility>

class Person {
 public:
  Person(std::string name, std::string gender, std::string maritalStatus) : name_(std::move(name)), gender_(std::move(gender)),
                                                                            maritalStatus_(std::move(maritalStatus)) {

  }
  [[nodiscard]] std::string getName() const {
      return name_;
  }
  [[nodiscard]] std::string getGender() const {
      return gender_;
  }
  [[nodiscard]] std::string getMaritalStatus() const {
      return maritalStatus_;
  }
  bool operator==(const Person& other) const{
      return name_ == other.name_ && gender_ == other.gender_ && maritalStatus_ == other.maritalStatus_;
  }
 private:
  std::string name_;
  std::string gender_;
  std::string maritalStatus_;
};

class Criteria {
 public:
  virtual std::list<Person> meetCriteria(const std::list<Person> &persons) = 0;
  virtual ~Criteria()= default;
};

class CriteriaMale : public Criteria {
 public:
  std::list<Person> meetCriteria(const std::list<Person> &persons) override {
      std::list<Person> malePersons;
      for (auto &person: persons) {
          if (person.getGender() == "MALE") {
              malePersons.push_back(person);
          }
      }
      return malePersons;
  }
};

class CriteriaFemale : public Criteria {
 public:
  std::list<Person> meetCriteria(const std::list<Person> &persons) override {
      std::list<Person> femalePersons;
      for (auto &person: persons) {
          if (person.getGender() == "FEMALE") {
              femalePersons.push_back(person);
          }
      }
      return femalePersons;
  }
};

class CriterSingle : public Criteria {
 public:
  std::list<Person> meetCriteria(const std::list<Person> &persons) override {
      std::list<Person> singlePersons;
      for (const Person &person: persons) {
          if (person.getMaritalStatus() == "SINGLE") {
              singlePersons.push_back(person);
          }
      }
      return singlePersons;
  }
};

class AndCriteria : public Criteria {
 public:
  AndCriteria(Criteria *criteria, Criteria *otherCriteria) : criteria_(criteria), otherCriteria_(otherCriteria) {

  }
  std::list<Person> meetCriteria(const std::list<Person> &persons) override {
      std::list<Person> firstCriterPersons = criteria_->meetCriteria(persons);
      return otherCriteria_->meetCriteria(firstCriterPersons);
  }
 private:
  Criteria *criteria_;
  Criteria *otherCriteria_;
};

class OrCriteria : public Criteria {
 public:
  OrCriteria(Criteria *criteria, Criteria *otherCriteria) : criteria_(criteria), otherCriteria_(otherCriteria) {

  }
  std::list<Person> meetCriteria(const std::list<Person> &persons) override {
      std::list<Person> firstCriteriaItems = criteria_->meetCriteria(persons);
      std::list<Person> otherCriteriaItems = otherCriteria_->meetCriteria(persons);
      for (auto &person: otherCriteriaItems) {
          if (std::find(firstCriteriaItems.begin(), firstCriteriaItems.end(), person) == firstCriteriaItems.end()) {
              firstCriteriaItems.push_back(person);
          }
      }
      return firstCriteriaItems;
  }
 private:
  Criteria *criteria_;
  Criteria *otherCriteria_;
};


static void PrintPersons(const std::list<Person>& persons) {
    for (auto &person: persons) {
        std::cout << "Person : [ Name : " << person.getName() << ", Gender : "
                  << person.getGender() << ", Marital Status : " << person.getMaritalStatus() << " ]"
                  << std::endl;
    }
}
static void PrintPersons(std::list<Person>&& persons) {
    for (auto &person: persons) {
        std::cout << "Person : [ Name : " << person.getName() << ", Gender : "
                  << person.getGender() << ", Marital Status : " << person.getMaritalStatus() << " ]"
                  << std::endl;
    }
}

int main() {
    std::list<Person> persons;
    persons.emplace_back("Robert", "MALE", "SINGLE");
    persons.emplace_back("john", "MALE", "Married");
    persons.emplace_back("Laura", "FEMALE", "Married");
    persons.emplace_back("Diana", "FEMALE", "SINGLE");
    persons.emplace_back("Mike", "MALE", "SINGLE");
    persons.emplace_back("Boddy", "MALE", "SINGLE");
    Criteria *male = new CriteriaMale();
    Criteria *female = new CriteriaFemale();
    Criteria *single = new CriterSingle();
    Criteria *singleMale = new AndCriteria(single, male);
    Criteria *singleOrFemale = new OrCriteria(single, female);
    PrintPersons(male->meetCriteria(persons));
    PrintPersons(female->meetCriteria(persons));
    PrintPersons(single->meetCriteria(persons));
    PrintPersons(singleMale->meetCriteria(persons));
    PrintPersons(singleOrFemale->meetCriteria(persons));
    delete male;
    delete female;
    delete single;
    delete singleMale;
    delete singleOrFemale;
}

