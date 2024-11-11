#include "configManager.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <filesystem>

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

// Исправленный метод log
void ConfigManager::log(const std::string &message, const std::string &username, const std::string &botResponse) {
    // Получение текущего времени
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");  // Формат времени
    std::string timeStr = oss.str();

    // Форматирование сообщения с информацией о пользователе и ответе
    std::string logMessage = "[" + timeStr + "] " + message;
    if (!username.empty()) {
        logMessage += " | User: " + username;
    }
    if (!botResponse.empty()) {
        logMessage += " | Bot response: " + botResponse;
    }

    // Вывод в консоль
    std::cout << logMessage << std::endl;

    // Создание директории для логов, если не существует
    std::filesystem::create_directories("../logs");

    // Запись в лог-файл
    std::ofstream logFile("../logs/bot.log", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << logMessage << std::endl;
    } else {
        std::cerr << "Error: Cannot open log file for writing." << std::endl;
    }
}
