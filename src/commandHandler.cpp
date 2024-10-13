#include "commandHandler.h"
#include <cstdlib>
#include <fstream>
#include <string>

using std::fstream, std::getline;

string CommandHandler::handleCommand(const string &command, const string &argument) {
    if (command == "/help") {
        return botHandleHelp();
    } else if (command == "/ping") {
        return botHandlePing(argument);
    } else if (command == "/status") {
        return botHandleStatus();
    } else if (command == "/anon") {
        return botHandleAnon(argument);
    } else {
        return botHandleUnknown();
    }
}

string CommandHandler::botHandleHelp() {
    return "List of available commands: \n/ping <website>\n/help\n/status\n/anon <address@xmpp.com> <message>\n";
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
