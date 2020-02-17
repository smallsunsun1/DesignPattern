//
// Created by 孙嘉禾 on 2020/1/18.
//

#include <string>
#include <iostream>
#include <vector>

class ComputerPart;
class KeyBoard;
class Mouse;
class Computer;
class Monitor;
class ComputerPartVisitor {
 public:
  virtual void Visit(Computer* computer) = 0;
  virtual void Visit(Mouse* mouse) = 0;
  virtual void Visit(KeyBoard* key_board) = 0;
  virtual void Visit(Monitor* monitor) = 0;
  virtual ~ComputerPartVisitor() = default;
};

class ComputerPartDisplayVisitor: public ComputerPartVisitor {
  void Visit(Computer *computer) override {
    std::cout << "Displaying Computer." << std::endl;
  }
  void Visit(Mouse *mouse) override {
    std::cout << "Displaying Mouse." << std::endl;
  }
  void Visit(KeyBoard *key_board) override {
    std::cout << "Displaying Keyboard." << std::endl;
  }
  void Visit(Monitor *monitor) override {
    std::cout << "Displaying Monitor." << std::endl;
  }
};

class ComputerPart {
 public:
  virtual void Accept(ComputerPartVisitor *compute_part_visitor) = 0;
  virtual ~ComputerPart() = default;
};

class KeyBoard : public ComputerPart {
 public:
  void Accept(ComputerPartVisitor *compute_part_visitor) override {
    compute_part_visitor->Visit(this);
  }
};

class Monitor: public ComputerPart{
 public:
  void Accept(ComputerPartVisitor *compute_part_visitor) override {
    compute_part_visitor->Visit(this);
  }
};

class Mouse: public ComputerPart {
 public:
  void Accept(ComputerPartVisitor *compute_part_visitor) override {
    compute_part_visitor->Visit(this);
  }
};

class Computer: public ComputerPart {
 public:
  Computer() {
    parts.push_back(new Mouse());
    parts.push_back(new KeyBoard());
    parts.push_back(new Monitor());
  }
  void Accept(ComputerPartVisitor *compute_part_visitor) override {
    for (int i = 0; i < parts.size(); ++i) {
      parts[i]->Accept(compute_part_visitor);
    }
    compute_part_visitor->Visit(this);
  }
  ~Computer() override {
    for (auto value: parts) {
      delete value;
    }
  }
 private:
  std::vector<ComputerPart*> parts;
};

int main() {
  Computer computer;
  auto visitor = new ComputerPartDisplayVisitor();
  computer.Accept(visitor);
  delete visitor;
  return 0;
}
