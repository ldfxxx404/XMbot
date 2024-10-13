#include "XMbot.h"

int main() {
    ConfigManager configManager;

    std::string username = configManager.getEnvVariable("USERNAME");
    std::string password = configManager.getEnvVariable("PASSWORD");

    if (username.empty() || password.empty()) {
        std::cerr << "Error. Username and password not found!" << std::endl;
        return 1;
    }

    XMbot bot(username, password);
    bot.run();
    return 0;
}
