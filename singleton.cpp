//
// Created by 孙嘉禾 on 2020/1/20.
//

#include <thread>
#include <iostream>
#include <future>

class SingleTon {
 private:
  SingleTon() { val = 4; };
  SingleTon(const SingleTon &) = delete;
  SingleTon &operator=(const SingleTon &) = delete;
  int val;
 public:
  static SingleTon &GetInstance() {
    static SingleTon instance;
    return instance;
  }
};

SingleTon &InitSingleTon() {
  return SingleTon::GetInstance();
}

int main() {
  auto res = std::async(InitSingleTon);
  std::thread t(InitSingleTon);
  auto& sig0 = res.get();
  auto& sig1 = SingleTon::GetInstance();
  auto& sig2 = SingleTon::GetInstance();
  std::cout << &(SingleTon::GetInstance()) << std::endl;
  std::cout << &(SingleTon::GetInstance()) << std::endl;
  std::cout << &(sig1) << std::endl;
  std::cout << &(sig0) << std::endl;
  if (t.joinable())
    t.join();
  return 0;
}

