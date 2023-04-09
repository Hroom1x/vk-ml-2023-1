#include "ioperation.hpp"
#include "parser.hpp"


int run(std::string& args) {
    std::vector<std::string> commands;
    std::vector<std::string> arguments;
    if (parseString(args, commands, arguments)) {
        return EINVAL;
    }
    if (commands.empty() || arguments.empty()) {
        std::cerr << "Invalid arguments" << std::endl;
        return EINVAL;
    }
    std::shared_ptr<IOperation> first_operation = createChild(commands[0]);
    first_operation->ProcessLine(arguments[0]);
    std::shared_ptr<IOperation> current_operation = first_operation;
    for (std::size_t i = 1; i < commands.size(); ++i) {
        auto temp = createChild(commands[i]);
        temp->ProcessLine(arguments[i]);
        current_operation->SetNextOperation(temp);
        current_operation = std::move(temp);
    }
    first_operation->HandleEndOfInput();
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Invalid arguments" << std::endl;
        return EINVAL;
    }
    std::string input(argv[1]);
    return run(input);
}
