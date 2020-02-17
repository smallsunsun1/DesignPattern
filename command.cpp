//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <iostream>
#include <string>
#include <list>

class Order {
 public:
  virtual void Execute() = 0;
  virtual ~Order() = default;
};

class Stock {
 public:
  void Buy() {
    std::cout << "Stock [ Name: " + name_ + ", Quantity: " + std::to_string(quantity)
     + " ] bought" << std::endl;
  }
  void Sell() {
    std::cout << "Stock [ Name: " + name_ + ", Quantity: " + std::to_string(quantity)
    + " ] sold" << std::endl;
  }
 private:
  std::string name_ = "ABC";
  int quantity = 10;
};

class BuyStock: public Order {
 public:
  explicit BuyStock(Stock* abc_stock): abc_stock_(abc_stock){}
  void Execute() override {
    abc_stock_->Buy();
  }
 private:
  Stock* abc_stock_;
};

class SellStock: public Order {
 public:
  explicit SellStock(Stock* abc_stock):abc_stock_(abc_stock) {

  }
  void Execute() override {
    abc_stock_->Sell();
  }
 private:
  Stock* abc_stock_;
};

class Broker {
 public:
  void TakeOrder(Order* order) {
    order_list_.push_back(order);
  }
  void PlaceOrders() {
    for (auto order: order_list_) {
      order->Execute();
    }
  }
 private:
  std::list<Order*> order_list_;
};

int main() {
  auto abcStock = new Stock();
  BuyStock* buy_stock = new BuyStock(abcStock);
  SellStock* sell_stock = new SellStock(abcStock);
  Broker broker;
  broker.TakeOrder(buy_stock);
  broker.TakeOrder(sell_stock);
  broker.PlaceOrders();
  delete abcStock;
  delete buy_stock;
  delete sell_stock;
}

