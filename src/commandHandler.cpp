#include "commandHandler.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <memory>
#include <stdexcept>
#include <filesystem>
#include <iostream>   // For std::cerr
#include <cstring>    // For strerror

using std::fstream, std::getline;

std::string CommandHandler::handleCommand(const std::string &command, const std::string &argument) {
    if (command == "/help") {
        return botHandleHelp();
    } else if (command == "/joke") {
        return botHandleJoke();
    } else if (command == "/status") {
        return botHandleStatus();
    } else if (command == "/anon") {
        return botHandleAnon(argument);
    } else if (command == "/news") { 
        return botHandleNews(); 
    } else if (command == "/weth") {
        return botHandleWeather(argument);
    } else {
        return botHandleUnknown();
    }
}

std::string CommandHandler::botHandleWeather(const std::string &city) {
    // Ensure the 'tmp' directory exists
    std::filesystem::create_directory("../tmp");

    // Write the city name to 'wthet_inpyt.txt'
    std::ofstream inputFile("../tmp/wthet_inpyt.txt");
    if (!inputFile) {
        std::cerr << "Error opening input file: " << strerror(errno) << std::endl;
        return "Error: Could not open input file.";
    }
    inputFile << city;
    inputFile.close();

    // Execute the Python script, specifying the input and output files
    int result = std::system("python3 ../scripts/wether.py ../tmp/wthet_inpyt.txt ../tmp/wthet_outpyt.txt");
    if (result != 0) {
        std::cerr << "Error executing Python script." << std::endl;
        return "Error: Could not execute Python script.";
    }

    // Read the result from 'wthet_outpyt.txt'
    std::ifstream outputFile("../tmp/wthet_outpyt.txt");
    if (!outputFile) {
        std::cerr << "Error opening output file: " << strerror(errno) << std::endl;
        return "Error: Could not open output file.";
    }
    std::string resultText((std::istreambuf_iterator<char>(outputFile)), std::istreambuf_iterator<char>());
    outputFile.close();

    return resultText;
}

std::string CommandHandler::botHandleJoke() {
    std::string command = "python3 ../scripts/joke.py";
    
    // Use popen for better control over the process
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        std::cerr << "Error executing joke script." << std::endl;
        return "Error: Could not execute joke script.";
    }

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }
    
    return result;  
}

std::string CommandHandler::botHandleHelp() {
    return "List of available commands: \n"
           "/help - Show this help message\n"
           "/status - Get the bot's current status\n"
           "/anon <address@xmpp.com> <message> - Send an anonymous message\n"
           "/news - Get the latest news updates\n"
           "/joke - Wakes up the bot's sense of humor\n"
           "/weth <city_name> - Get the weather for the specified city";  // Updated the description for /weth
}

std::string CommandHandler::botHandleStatus() {
    return "Bot is running\n";
}

std::string CommandHandler::botHandleUnknown() {
    return "Unknown command! Try /help for more information";
}

std::string CommandHandler::botHandleAnon(const std::string &argument) {
    size_t firstSpacePosition = argument.find(' ');
    if (firstSpacePosition == std::string::npos) {
        return "Error: Incorrect format. Use /anon <address@xmpp.com> <message>";
    }
    
    std::string recipient = argument.substr(0, firstSpacePosition);
    std::string message = argument.substr(firstSpacePosition + 1);
    
    if (message.empty()) {
        return "Error: Message cannot be empty.";
    }
    return "Sending message to: " + recipient + "\nMessage: " + message;
}

std::string CommandHandler::botHandleNews() { // Handling /news
    std::string command = "python3 ../scripts/main.py"; // Path to your Python script

    // Use popen to capture script output
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        std::cerr << "Error executing news script." << std::endl;
        return "Error: Could not execute news script.";
    }

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer; // Append script output
    }

    // Return the result
    if (result.empty()) {
        return "No news available.";
    }

    return result; // Returning the result to the user
}
