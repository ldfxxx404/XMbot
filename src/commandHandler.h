#ifndef COMMAND_HANLDLER_H
#define COMMAND_HANLDLER_H

#include <string>

using std::string;

class CommandHandler {
public:
  string handleCommand(const string &command, const string &argument = "");

private:
  std::string botHandleHelp();
  std::string botHandlePing(const std::string &website);
  std::string botHandleStatus();
  std::string botHandleUnknown();
};

#endif // COMMAND_HANLDLER_H
