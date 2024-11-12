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

        // Теперь передаем client как параметр
        std::string response = commandHandler.handleCommand(client, command, argument);

        // Логируем ответ от бота с указанием пользователя
        configManager.log("Sending bot response", msg.from().bare(), response);

        // Отправляем ответ обратно пользователю
        Message reply(gloox::Message::Chat, msg.from(), response);
        client.send(reply);
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
    configManager.log("Log entry", "Level " + std::to_string(level), message);
}

void XMbot::run() {
    client.connect();
}
