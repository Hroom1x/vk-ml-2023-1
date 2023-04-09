#pragma once

#include <cerrno>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>


class IOperation {
public:
    virtual void ProcessLine(const std::string& str) = 0;                             // String to feed to operation
    virtual void HandleEndOfInput() = 0;                                              // End of operation and start next operation
    virtual void SetNextOperation(std::shared_ptr<IOperation>& next_operation) = 0;  // Set next operation
};

class Echo : public IOperation {
public:
    Echo() : _argument(std::string("")) { };

    void ProcessLine(const std::string& str) override;
    void HandleEndOfInput() override;
    void SetNextOperation(std::shared_ptr<IOperation>& next_operation) override;
private:
    std::string _argument;
    std::shared_ptr<IOperation> _next_operation;
};

class Cat : public IOperation {
public:
    Cat() : _argument(std::string("")) { };

    void ProcessLine(const std::string& str) override;
    void HandleEndOfInput() override;
    void SetNextOperation(std::shared_ptr<IOperation>& next_operation) override;
private:
    std::string _argument;
    std::shared_ptr<IOperation> _next_operation;
};

class Nl : public IOperation {
public:
    Nl() : _argument(std::string("")) { };

    void ProcessLine(const std::string& str) override;
    void HandleEndOfInput() override;
    void SetNextOperation(std::shared_ptr<IOperation>& next_operation) override;
private:
    std::string _argument;
    std::shared_ptr<IOperation> _next_operation;
};

// Factory function
std::shared_ptr<IOperation> createChild(const std::string &type);
