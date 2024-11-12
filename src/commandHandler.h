#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <string>
#include <gloox/client.h>   // Для gloox::Client
#include <gloox/message.h>  // Для gloox::Message

using std::string;

class CommandHandler {
public:
    // Передаем client сюда
    string handleCommand(gloox::Client &client, const string &command, const string &argument = "");
    string botHandleAnon(gloox::Client &client, const gloox::Message &msg, const string &argument);  // Передаем client и msg как параметры
    string botHandleNews();
    string botHandleJoke();
    string botHandleWeather(const string &argument);

private:
    string botHandleHelp();
    string botHandleStatus();
    string botHandleUnknown();
};

#endif // COMMAND_HANDLER_H
