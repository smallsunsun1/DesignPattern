//
// Created by 孙嘉禾 on 2020/1/17.
//

#include <string>
#include <iostream>

class AbstractLogger {
 public:
  constexpr static int INFO = 1;
  constexpr static int DEBUG = 2;
  constexpr static int ERROR = 3;
  void SetNextLogger(AbstractLogger *nextlogger) {
      nextLogger_ = nextlogger;
  }
  void LogMessage(int level, std::string message) {
      if (level_ <= level) {
          Write(message);
      }
      if (nextLogger_ != nullptr) {
          nextLogger_->LogMessage(level, message);
      }
  }
  virtual ~AbstractLogger() {
      delete nextLogger_;
  }
 protected:
  virtual void Write(std::string message) = 0;
  int level_;
  AbstractLogger *nextLogger_;
};

class ConsoleLogger : public AbstractLogger {
 public:
  explicit ConsoleLogger(int level) {
      level_ = level;
      nextLogger_ = nullptr;
  }
 protected:
  void Write(std::string message) override {
      std::cout << "Standatd Condole::Logger: " + message << std::endl;
  }
};

class ErrorLogger : public AbstractLogger {
 public:
  explicit ErrorLogger(int level) {
      level_ = level;
      nextLogger_ = nullptr;
  }
 protected:
  void Write(std::string message) override {
      std::cout << "Error Console::Logger: " + message << std::endl;
  }
};

class FileLogger: public AbstractLogger {
 public:
  explicit FileLogger(int level) {
      level_ = level;
      nextLogger_ = nullptr;
  }
 protected:
  void Write(std::string message) override {
     std::cout << "File::Logger: " + message << std::endl;
 }
};

//创建不同类型的记录器。赋予它们不同的错误级别，并在每个记录器中设置下一个记录器。每个记录器中的下一个记录器代表的是链的一部分。

class ChainPatternDemo {
 public:
  static AbstractLogger* GetChainOfLoggers() {
      AbstractLogger* errorLogger = new ErrorLogger(AbstractLogger::ERROR);
      AbstractLogger* fileLogger = new FileLogger(AbstractLogger::DEBUG);
      AbstractLogger* consoleLogger = new ConsoleLogger(AbstractLogger::INFO);
      errorLogger->SetNextLogger(fileLogger);
      fileLogger->SetNextLogger(consoleLogger);
      return errorLogger;
  }
};

int main(int argc, char* argv[]) {
    AbstractLogger* loggerChain = ChainPatternDemo::GetChainOfLoggers();
    loggerChain->LogMessage(AbstractLogger::INFO, "This is an information.");
    loggerChain->LogMessage(AbstractLogger::DEBUG, "This is a debug level information.");
    loggerChain->LogMessage(AbstractLogger::ERROR, "This is an error information.");
    delete loggerChain;
    return 0;
}
