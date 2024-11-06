#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <string>

using std::string;

class CommandHandler {
public:
    string handleCommand(const string &command, const string &argument = "");
    string botHandleAnon(const string &argument);
    string botHandleNews(); // Новый метод для обработки /news
    string botHandleJoke();
    string botHandleWeather(const string &argument);

private:
    string botHandleHelp();
    string botHandlePing(const string &website);
    string botHandleStatus();
    string botHandleUnknown();
};

#endif // COMMAND_HANDLER_H
