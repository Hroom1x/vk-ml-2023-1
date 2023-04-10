#pragma once

#include <cerrno>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>


const std::size_t MAX_LINE_SIZE = 65536;

struct File {
public:
    File() : _file(nullptr) {};
    File(const std::string& str) : _file(nullptr) { _file.open(str); }
    ~File() { if (_file) _file.close(); }

    void open(const std::string& str) {
        _file.open(str);
    }

    std::ifstream _file;
};

class IOperation {
public:
    virtual void ProcessLine(const std::string& str) = 0;                            // String to feed to operation
    virtual void HandleEndOfInput() = 0;                                             // End of operation and start next operation
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
    Cat() = default;

    void ProcessLine(const std::string& str) override;
    void HandleEndOfInput() override;
    void SetNextOperation(std::shared_ptr<IOperation>& next_operation) override;
private:
    File _file;
    std::string _argument;
    std::shared_ptr<IOperation> _next_operation;
};

class Nl : public IOperation {
public:
    Nl() = default;

    void ProcessLine(const std::string& str) override;
    void HandleEndOfInput() override;
    void SetNextOperation(std::shared_ptr<IOperation>& next_operation) override;
private:
    File _file;
    std::string _argument;
    std::shared_ptr<IOperation> _next_operation;
};

// Factory function
std::shared_ptr<IOperation> createChild(const std::string &type);
