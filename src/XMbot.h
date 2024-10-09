#ifndef XMBOT_H
#define XMBOT_H

#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/loghandler.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/messagesession.h>
#include <iostream>
#include "commandHandler.h"

using namespace gloox;

class XMbot : public MessageHandler,
              public ConnectionListener,
              public LogHandler {
public:
  XMbot(const std::string &jid, const std::string &password);

  void handleMessage(const Message &msg, MessageSession *session) override;

  void onConnect() override;
  void onDisconnect(ConnectionError e) override;
  bool onTLSConnect(const CertInfo &info) override;

  void handleLog(LogLevel level, LogArea area,
                 const std::string &message) override;

  void run();

private:
  Client client;
  CommandHandler commandHandler;
};

#endif // XMBOT_H
