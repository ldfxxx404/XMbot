#include "commandHandler.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <memory> // Добавлено для std::shared_ptr
#include <stdexcept>

using std::fstream, std::getline;

string CommandHandler::handleCommand(const string &command, const string &argument) {
    if (command == "/help") {
        return botHandleHelp();
    } else if (command == "/joke") {
        return botHandleJoke();
    } else if (command == "/ping") {
        return botHandlePing(argument);
    } else if (command == "/status") {
        return botHandleStatus();
    } else if (command == "/anon") {
        return botHandleAnon(argument);
    } else if (command == "/news") {  // Обработка новой команды /news
        return botHandleNews();
    } else {
        return botHandleUnknown();
    }
}
string CommandHandler::botHandleJoke() {
    std::string command = "python3 ../scripts/joke.py";
    
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    char buffer[128];
    std::string result;
    
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }
    
    return result;  
}

string CommandHandler::botHandleHelp() {
    return "List of available commands: \n"
           "/ping <website> - Check if a website is reachable\n"
           "/help - Show this help message\n"
           "/status - Get the bot's current status\n"
           "/anon <address@xmpp.com> <message> - Send an anonymous message\n"
           "/news - Get the latest news updates\n"
           "/joke - Воспроизводит случайную хохму"; // Добавляем команду /news
}

string CommandHandler::botHandlePing(const string &website) {
    string tempPingOutput = "/tmp/tempPingOutput.txt";
    string command = "ping -c 1 " + website + " > " + tempPingOutput;
    system(command.c_str());
    
    fstream file(tempPingOutput);
    string line, result;
    if (file.is_open()) {
        while (getline(file, line)) {
            result += line + "\n";
        }
        file.close();
    }
    return result;
}

string CommandHandler::botHandleStatus() {
    return "Bot is running\n";
}

string CommandHandler::botHandleUnknown() {
    return "Unknown command! Try /help for more information";
}

string CommandHandler::botHandleAnon(const string &argument) {
    size_t firstSpacePosition = argument.find(' ');
    if (firstSpacePosition == string::npos) {
        return "Error: Incorrect format. Use /anon <address@xmpp.com> <message>";
    }
    
    string recipient = argument.substr(0, firstSpacePosition);
    string message = argument.substr(firstSpacePosition + 1);
    
    if (message.empty()) {
        return "Error: Message cannot be empty.";
    }
    return "Sending message to: " + recipient + "\nMessage: " + message;
}

string CommandHandler::botHandleNews() { // Новый метод для обработки /news
    string command = "python3 ../scripts/main.py"; // Путь к вашему Python скрипту

    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    char buffer[128];
    string result;
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer; // Сохраняем вывод скрипта
    }

    // Проверка на пустой результат
    if (result.empty()) {
        return "No news available.";
    }

    return result; // Возвращаем результат, который будет отправлен пользователю
}