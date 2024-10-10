#ifndef COMMAND_HANLDLER_H
#define COMMAND_HANLDLER_H

#include <string>

using std::string;

class CommandHandler {
public:
  string handleCommand(const string &command, const string &argument = "");
  string botHandleAnon(const string &argument);

private:
  string botHandleHelp();
  string botHandlePing(const string &website);
  string botHandleStatus();
  string botHandleUnknown();
  };

#endif // COMMAND_HANLDLER_H
