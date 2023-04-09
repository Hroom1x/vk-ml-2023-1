#include "ioperation.hpp"
#include "parser.hpp"


int run(std::string& args) {
    std::vector<std::string> commands;
    std::vector<std::string> arguments;
    parseString(args, commands, arguments);
    if (commands.empty() || arguments.empty()) {
        std::cerr << "Invalid arguments" << std::endl;
        return EINVAL;
    }
    /*auto first_operaion = std::make_unique<IOperation>();
    for (std::size_t i = 1; i < commands.size(); ++i) {
        //
    }*/
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    return EXIT_SUCCESS;
}
