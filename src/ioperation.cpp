#include "ioperation.hpp"


void Echo::ProcessLine(const std::string& str) {
    _argument = str;
}

void Echo::HandleEndOfInput() {
    std::cout << _argument << std::endl;
    if (_next_operation)
        _next_operation->HandleEndOfInput();
}

void Echo::SetNextOperation(std::shared_ptr<IOperation>& next_operation) {
    _next_operation = next_operation;
}

void Cat::ProcessLine(const std::string &str) {
    _argument = str;
    _file.open(_argument);
}

void Cat::HandleEndOfInput() {
    if (_file._file.is_open()) {
        std::cout << _file._file.rdbuf();
        std::cout << std::endl;
    }
    if (_next_operation)
        _next_operation->HandleEndOfInput();
}

void Cat::SetNextOperation(std::shared_ptr<IOperation>& next_operation) {
    _next_operation = next_operation;
}

void Nl::ProcessLine(const std::string &str) {
    _argument = str;
}

void Nl::HandleEndOfInput() {
    std::cout << _argument << std::endl;
    if (_next_operation)
        _next_operation->HandleEndOfInput();
}

void Nl::SetNextOperation(std::shared_ptr<IOperation>& next_operation) {
    _next_operation = next_operation;
}

std::shared_ptr<IOperation> createChild(const std::string &type) {
    if (type == "echo") {
        return std::make_shared<Echo>();
    } else if (type == "cat") {
        return std::make_shared<Cat>();
    } else if (type == "nl") {
        return std::make_shared<Nl>();
    } else {
        return nullptr;
    }
}
