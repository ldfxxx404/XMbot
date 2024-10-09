#include "commandHandler.h"
#include <cstdlib>
#include <fstream>

std::string CommandHandler::handleCommand(const std::string& command, const std::string& argument) {
    if (command == "/help") {
        return botHandleHelp();
    } else if (command == "/ping") {
        return botHandlePing(argument);
    } else if (command == "/status") {
        return botHandleStatus();
    } else {
        return botHandleUnknown();
    }
}

std::string CommandHandler::botHandleHelp() {
    return "List of available commands: \n/ping <website>\n/help\n/status\n";
}

std::string CommandHandler::botHandlePing(const std::string& website) {
    std::string tempPingOutput = "/tmp/tempPingOutput.txt";
    std::string command = "ping -c 1 " + website + " > " + tempPingOutput;
    system(command.c_str());
    std::fstream file(tempPingOutput);
    std::string line, result;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            result += line + "\n";
        }
        file.close();
    }
    return result;
}

std::string CommandHandler::botHandleStatus() {
    return "Bot is running\n";
}

std::string CommandHandler::botHandleUnknown() {
    return "Unknown command! Try /help for more information";
}

