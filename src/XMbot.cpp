#include "XMbot.h"
#include <gloox/gloox.h>
#include <gloox/jid.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/messagesession.h>
#include <string>

using std::string;

XMbot::XMbot(const string &jid, const string &password)
    : client(jid, password) {  // Удалена инициализация securityManager
    client.registerMessageHandler(this);
    client.registerConnectionListener(this);
    client.logInstance().registerLogHandler(LogLevelError, LogAreaAll, this);  
}

void XMbot::handleMessage(const Message &msg, MessageSession *session) {
    if (msg.subtype() == Message::Chat && !msg.body().empty()) {
        // Логируем получение сообщения
        configManager.log("Received message from " + msg.from().bare(), msg.from().bare(), msg.body());
    }

    std::string body = msg.body();
    if (body[0] == '/') {
        size_t spacePosition = body.find(' ');
        std::string command = body.substr(0, spacePosition);
        std::string argument = (spacePosition != std::string::npos) ? body.substr(spacePosition + 1) : "";

        // Получаем ответ от обработчика команд
        std::string response = commandHandler.handleCommand(command, argument);

        // Логируем ответ от бота с указанием пользователя
        configManager.log("Sending bot response", msg.from().bare(), response);

        // Отправляем ответ обратно пользователю
        Message reply(gloox::Message::Chat, msg.from(), response);
        client.send(reply);

        // Обработка команды /anon отдельно
        if (command == "/anon") {
            std::string response = commandHandler.botHandleAnon(argument);
            if (response.find("Error") == 0) {
                Message reply(Message::Chat, msg.from(), response);
                client.send(reply);
            } else {
                size_t firstSpacePosition = argument.find(' ');
                std::string recipient = argument.substr(0, firstSpacePosition);
                std::string message = argument.substr(firstSpacePosition + 1);
                Message anonMessage(Message::Chat, JID(recipient), message);
                client.send(anonMessage);

                // Логируем анонимное сообщение
                configManager.log("Sending anonymous message", recipient, message);
            }
        }
    }
}


void XMbot::onConnect() {
    configManager.log("Connected to XMPP server.");
}

void XMbot::onDisconnect(ConnectionError e) {
    configManager.log("Connection error. Error code: " + std::to_string(e));
}

bool XMbot::onTLSConnect(const CertInfo &info) {
    configManager.log("TLS connection is done");
    return true;
}

void XMbot::handleLog(LogLevel level, LogArea area, const string &message) {
    configManager.log("LOG [" + std::to_string(level) + "] (" + std::to_string(area) + "): " + message);
}

void XMbot::run() { client.connect(true); }
