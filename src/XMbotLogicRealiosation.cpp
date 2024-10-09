#include "XMbot.h"
// #include "commandList.h"
#include <cstddef>
#include <gloox/gloox.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/messagesession.h>
#include <string>

XMbot::XMbot(const std::string &jid, const std::string &password)
    : client(jid, password) {
  client.registerMessageHandler(this);
  client.registerConnectionListener(this);
  client.logInstance().registerLogHandler(LogLevelError, LogAreaUser, this);
}

void XMbot::handleMessage(const Message &msg, MessageSession *session) {
  if (msg.subtype() == Message::Chat && !msg.body().empty()) {
    std::cout << "Recived message from " << msg.from().bare() << std::endl;
    std::cout << "Text: " << msg.body() << std::endl;
  }

  std::string body = msg.body();
  if (body[0] == '/') {
    size_t spacePosition = body.find(' ');
    std::string command = body.substr(0, spacePosition);
    std::string argument = (spacePosition != std::string::npos)
                               ? body.substr(spacePosition + 1)
                               : "";
    std::string response = commandHandler.handleCommand(command, argument);
    Message reply(gloox::Message::Chat, msg.from(), response);
    client.send(reply);
  }
}

void XMbot::onConnect() {
  std::cout << "Connected to XMPP server." << std::endl;
}

void XMbot::onDisconnect(ConnectionError e) {
  std::cout << "Connection error. Error code: " << e << std::endl;
}

bool XMbot::onTLSConnect(const CertInfo &info) {
  std::cout << "TLS connection is done" << std::endl;
  return true;
}

void XMbot::handleLog(LogLevel level, LogArea area,
                      const std::string &message) {
  std::cout << "LOG [" << level << "] (" << area << "): " << message
            << std::endl;
}

void XMbot::run() { client.connect(true); }
