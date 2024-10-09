#ifndef COMMAND_LIST
#define COMMAND_LIST

#include <gloox/message.h>
#include <string>

using std::string;

string botHelpCommandHandler();
string botPingCommandHandler(const std::string &website);
string botUnknownCommandHandler();
string botStatusCommandHandler();

#endif // COMMAND_LIST
