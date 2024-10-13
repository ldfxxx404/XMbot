#include "configManager.h"
#include <fstream>
#include <iostream>

std::string ConfigManager::getEnvVariable(const std::string &key) {
    std::ifstream envFile("../.env");
    if (!envFile.is_open()) {
        log("Error: .env file not found or can't be opened.");
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

void ConfigManager::log(const std::string &message) {
    std::cout << message << std::endl; // You could extend this to log to a file
}
