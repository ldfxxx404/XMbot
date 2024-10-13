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
        configManager.log("Received message from " + msg.from().bare());
        configManager.log("Text: " + msg.body());
    }

    string body = msg.body();
    if (body[0] == '/') {
        size_t spacePosition = body.find(' ');
        string command = body.substr(0, spacePosition);
        string argument = (spacePosition != string::npos) ? body.substr(spacePosition + 1) : "";

        string response = commandHandler.handleCommand(command, argument);
        Message reply(gloox::Message::Chat, msg.from(), response);
        client.send(reply);

        if (command == "/anon") {
            string response = commandHandler.botHandleAnon(argument);
            if (response.find("Error") == 0) {
                Message reply(Message::Chat, msg.from(), response);
                client.send(reply);
            } else {
                size_t firstSpacePosition = argument.find(' ');
                string recipient = argument.substr(0, firstSpacePosition);
                string message = argument.substr(firstSpacePosition + 1);
                Message anonMessage(Message::Chat, JID(recipient), message);
                client.send(anonMessage);
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
