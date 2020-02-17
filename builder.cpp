//
// Created by 孙嘉禾 on 2020/1/20.
//

#include <iostream>
#include <string>
#include <list>

class Pack {
 public:
  virtual std::string pack() = 0;
  virtual ~Pack() = default;
};

class Item {
 public:
  virtual std::string Name() = 0;
  virtual Pack* Packing() = 0;
  virtual float Price() = 0;
  virtual ~Item() = default;
};

class Wrapper: public Pack {
 public:
  std::string pack() override {
    return "Wrapper";
  }
};

class Bottle: public Pack {
  std::string pack() override {
    return "Bottle";
  }
};

class Burger: public Item {
 public:
  Pack* Packing() override {
    return new Wrapper();
  }
};

class ColdDrink: public Item {
  Pack * Packing() override {
    return new Bottle();
  }
};

class VegBurger: public Burger {
 public:
  float Price() override {
    return 25.0;
  }
  std::string Name() override {
    return "Veg Burger";
  }
};

class ChickenBurger: public Burger {
 public:
  float Price() override {
    return 50.5;
  }
  std::string Name() override {
    return "Chicken Burger";
  }
};

class Coke: public ColdDrink {
 public:
  float Price() override {
    return 30.0;
  }
  std::string Name() override {
    return "Coke";
  }
};

class Pepsi: public ColdDrink {
  float Price() override {
    return 35.0;
  }
  std::string Name() override {
    return "Pepsi";
  }
};

class Meal {
 public:
  void AddItem(Item* item) {items_.push_back(item);}
  float GetCost() {
    float cost = 0;
    for (Item* item: items_){
      cost += item->Price();
    }
    return cost;
  }
  void ShowItems() {
    for (Item* item: items_) {
      std::cout << "Item : " + item->Name() << std::endl;
      auto pack = item->Packing();
      std::cout << ", Packing : " + pack->pack() << std::endl;
      std::cout << ", Price : " + std::to_string(item->Price()) << std::endl;
      delete pack;
    }
  }
  ~Meal(){
    for (auto value: items_) {
      delete value;
    }
  }
 private:
  std::list<Item*> items_;
};

class MealBuilder {
 public:
  static Meal* PrepareVegMeal() {
    Meal* meal = new Meal();
    meal->AddItem(new VegBurger());
    meal->AddItem(new Coke());
    return meal;
  }
  static Meal* PrepareNonVegMeal() {
    Meal* meal = new Meal();
    meal->AddItem(new ChickenBurger());
    meal->AddItem(new Pepsi());
    return meal;
  }
};

int main() {
  Meal* veg_meal = MealBuilder::PrepareNonVegMeal();
  veg_meal->ShowItems();
  std::cout << veg_meal->GetCost() << std::endl;
  delete veg_meal;
}

