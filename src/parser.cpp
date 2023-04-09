#include "parser.hpp"


int parseString(std::string& str, std::vector<std::string>& commands, std::vector<std::string>& arguments) {
    if (str.empty()) {
        std::cerr << "Empty string" << std::endl;
        return EINVAL;
    }
    std::string current_command;
    std::string current_argument;
    for (std::size_t i = 0; i < str.size();) {
        // Extract current command
        while (str[i] != ' ' && i < str.size()) {
            current_command += str[i];
            i++;
        }

        if (i < str.size() && str[i] == ' ') {
            ++i;
        } else {
            std::cerr << "Invalid argument";
            return EINVAL;
        }

        // Extract current argument
        while (str[i] != ' ' && i < str.size()) {
            current_argument += str[i];
            i++;
        }
        if (!current_argument.empty()) {
            if (current_command == "echo" || current_command == "cat" || current_command == "nl") {
                commands.push_back(current_command);
                arguments.push_back(current_argument);
            } else {
                std::cerr << "Unknown command";
                return EINVAL;
            }
        } else {
            std::cerr << "Invalid argument";
            return EINVAL;
        }

        // Skip space
        if (i < str.size() && str[i] == ' ') {
            ++i;
        }
        // Check for separation symbol
        if (str[i] == '|') {
            i++;
        }
        // Skip space
        if (i < str.size() && str[i] == ' ') {
            ++i;
        }

        current_command = "";
        current_argument = "";
    }
    return 0;
}
