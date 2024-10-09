#include "XMbot.h"
#include "commandList.h"
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
  if (body.find("/") != 0){
    std::cout << "Not command, ignore\n";
    return;
  }
  if (body == "/status" || body == "/status ") {
    Message reply(Message::Chat, msg.from(), botStatusCommandHandler());
    client.send(reply);
  } else if (body == "/help" || body == "/help ") {
    Message reply(Message::Chat, msg.from(), botHelpCommandHandler());
    client.send(reply);
  } else if (body == "/ping" || body == "/ping ") {
    std::string website = "google.com";
    Message reply(Message::Chat, msg.from(), botPingCommandHandler(website));
    client.send(reply);
  } else {
    Message reply(Message::Chat, msg.from(), botUnknownCommandHandler());
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
