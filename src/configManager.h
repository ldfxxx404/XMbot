#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>

class ConfigManager {
public:
    std::string getEnvVariable(const std::string &key);

    // Обновленный метод log с дополнительными параметрами и значениями по умолчанию
    void log(const std::string &message, const std::string &username = "", const std::string &botResponse = "");
};

#endif // CONFIG_MANAGER_H
