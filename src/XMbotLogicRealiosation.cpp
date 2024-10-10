#include "XMbot.h"
#include <cstddef>
#include <gloox/gloox.h>
#include <gloox/jid.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/messagesession.h>
#include <string>

using std::string;

XMbot::XMbot(const string &jid, const string &password)
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
    string command = body.substr(0, spacePosition);
    string argument =
        (spacePosition != string::npos) ? body.substr(spacePosition + 1) : "";

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
  std::cout << "Connected to XMPP server." << std::endl;
}

void XMbot::onDisconnect(ConnectionError e) {
  std::cout << "Connection error. Error code: " << e << std::endl;
}

bool XMbot::onTLSConnect(const CertInfo &info) {
  std::cout << "TLS connection is done" << std::endl;
  return true;
}

void XMbot::handleLog(LogLevel level, LogArea area, const string &message) {
  std::cout << "LOG [" << level << "] (" << area << "): " << message
            << std::endl;
}

void XMbot::run() { client.connect(true); }
