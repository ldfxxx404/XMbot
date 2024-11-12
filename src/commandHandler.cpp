#include "commandHandler.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <memory>
#include <stdexcept>
#include <filesystem>
#include <iostream>
#include <cstring>
#include <gloox/message.h>  // Для использования gloox::Message
#include <gloox/jid.h>

using std::fstream, std::getline;

std::string CommandHandler::handleCommand(gloox::Client &client, const std::string &command, const std::string &argument) {
    if (command == "/help") {
        return botHandleHelp();
    } else if (command == "/joke") {
        return botHandleJoke();
    } else if (command == "/status") {
        return botHandleStatus();
    } else if (command == "/anon") {
        // Передаем правильный объект gloox::JID, а не строку
        size_t spacePosition = argument.find(' ');
        if (spacePosition == std::string::npos) {
            return "Error: Invalid format. Use /anon <address@xmpp.com> <message>";
        }

        std::string recipient = argument.substr(0, spacePosition);
        std::string message = argument.substr(spacePosition + 1);
        gloox::JID jid(recipient); // Создаем объект JID для получателя
        gloox::Message msg(gloox::Message::Chat, jid, message); // Используем JID вместо строки

        return botHandleAnon(client, msg, message);  // Передаем client и сообщение
    } else if (command == "/news") { 
        return botHandleNews(); 
    } else if (command == "/weth") {
        return botHandleWeather(argument);
    } else {
        return botHandleUnknown();
    }
}

std::string CommandHandler::botHandleWeather(const std::string &city) {
    std::filesystem::create_directory("../tmp");

    std::ofstream inputFile("../tmp/wthet_inpyt.txt");
    if (!inputFile) {
        std::cerr << "Error opening input file: " << strerror(errno) << std::endl;
        return "Error: Could not open input file.";
    }
    inputFile << city;
    inputFile.close();

    int result = std::system("python3 ../scripts/wether.py ../tmp/wthet_inpyt.txt ../tmp/wthet_outpyt.txt");
    if (result != 0) {
        std::cerr << "Error executing Python script." << std::endl;
        return "Error: Could not execute Python script.";
    }

    std::ifstream outputFile("../tmp/wthet_outpyt.txt");
    if (!outputFile) {
        std::cerr << "Error opening output file: " << strerror(errno) << std::endl;
        return "Error: Could not open output file.";
    }
    std::string resultText((std::istreambuf_iterator<char>(outputFile)), std::istreambuf_iterator<char>());
    outputFile.close();

    return resultText;
}

std::string CommandHandler::botHandleJoke() {
    std::string command = "python3 ../scripts/joke.py";
    
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        std::cerr << "Error executing joke script." << std::endl;
        return "Error: Could not execute joke script.";
    }

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }
    
    return result;  
}

std::string CommandHandler::botHandleHelp() {
    return "List of available commands: \n"
           "/help - Show this help message\n"
           "/status - Get the bot's current status\n"
           "/anon <address@xmpp.com> <message> - Send an anonymous message\n"
           "/news - Get the latest news updates\n"
           "/joke - Wakes up the bot's sense of humor\n"
           "/weth <city_name> - Get the weather for the specified city";  // Updated the description for /weth
}

std::string CommandHandler::botHandleStatus() {
    return "Bot is running\n";
}

std::string CommandHandler::botHandleUnknown() {
    return "Unknown command! Try /help for more information";
}

std::string CommandHandler::botHandleNews() { 
    std::string command = "python3 ../scripts/main.py";

    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        std::cerr << "Error executing news script." << std::endl;
        return "Error: Could not execute news script.";
    }

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }

    return result.empty() ? "No news available." : result;
}

std::string CommandHandler::botHandleAnon(gloox::Client &client, const gloox::Message &msg, const std::string &argument) {
    // Логируем сообщение
    // configManager.log("Sending anonymous message to " + msg.to().full(), "Anonymous", argument);  // Убедитесь, что у вас есть доступ к configManager

    // Отправляем анонимное сообщение
    client.send(msg);

    return "Message sent to " + msg.to().full();
}
