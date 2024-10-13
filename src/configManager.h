#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>

class ConfigManager {
public:
    std::string getEnvVariable(const std::string &key);
    void log(const std::string &message);
};

#endif // CONFIG_MANAGER_H
