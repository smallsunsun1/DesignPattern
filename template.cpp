//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <string>
#include <iostream>

class Game {
 public:
  virtual void Initialize() = 0;
  virtual void StartPlay() = 0;
  virtual void EndPlay() = 0;
  virtual ~Game() = default;
  void Play() {
    Initialize();
    StartPlay();
    EndPlay();
  }
};

class Cricket: public Game {
  void EndPlay() override {
    std::cout << "Cricket Game Finished!" << std::endl;
  }
  void Initialize() override {
    std::cout << "Cricket Game Initialized! Start playing." << std::endl;
  }
  void StartPlay() override {
    std::cout << "Cricket Game Started. Enjoy the game!" << std::endl;
  }
};

int main() {
  Game* game = new Cricket();
  game->Play();
  delete game;
  return 0;
}
