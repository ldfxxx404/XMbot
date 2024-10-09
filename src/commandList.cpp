#include "commandList.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <gloox/message.h>
#include <string>

using std::string;

string botStatusCommandHandler() {
  return "Bot is running\n";
}

string botHelpCommandHandler() {
  return "List of available commands: \n"
         "/ping\n"
         "/help\n"
         "/status\n";
}


string botPingCommandHandler(const string &website) {
  string tempPingOutput = "/tmp/tempPingOutput.txt";
  string command = "ping -c 1 " + website + "> " + tempPingOutput;
  system(command.c_str());
  std::fstream file(tempPingOutput);
  string line, result;
  if (file.is_open()) {
    while (std::getline(file, line)) {
      result += line + "\n";
    }
    file.close();
  }
  return result;
}

string botUnknownCommandHandler() {
return "Unknown command! Try /help for more information";

}
