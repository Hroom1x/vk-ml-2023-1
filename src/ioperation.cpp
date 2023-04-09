#include "ioperation.hpp"


void Echo::ProcessLine(const std::string& str) {
    _argument = str;
}

void Echo::HandleEndOfInput() {
    std::cout << _argument << std::endl;
    _next_operation->HandleEndOfInput();
}

void Echo::SetNextOperation(std::unique_ptr<IOperation>&& next_operation) {
    _next_operation = std::move(next_operation);
}

