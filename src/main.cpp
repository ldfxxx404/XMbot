#include "XMbot.h"
#include <fstream>
#include <iostream>
#include <string>

std::string getEnvVariable(const std::string &key) {

  std::ifstream envFile("../.env");
  if (!envFile.is_open()) {
    std::cerr << "Error: .env file not find or can't be opened.\n";
    return "";
  }

  std::string line;
  while (std::getline(envFile, line)) {
    size_t pos = line.find('=');
    if (line.substr(0, pos) == key) {
      return line.substr(pos + 1);
    }
  }

  return "";
}

int main() {

  std::string username = getEnvVariable("USERNAME");
  std::string password = getEnvVariable("PASSWORD");

  if (username.empty() || password.empty()) {
    std::cerr << "Error. Username and password not found!" << std::endl;
    return 1;
  }

  XMbot bot(getEnvVariable("USERNAME"), getEnvVariable("PASSWORD"));
  bot.run();
  return 0;
}
