#pragma once

#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

const int NAME_ROW_LENGTH = 6;
const int TITLE_ROW_LENGTH = 9;
const int AKAS_ROW_LENGTH = 8;
const int ARG_NUMBER = 9;
const int TCONST_NUM_LENGTH = 7;


class FileHandler {
public:
    FileHandler() : file() {}

    bool open(const std::string& filename) {
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return true;
        }
        return false;
    }

    ~FileHandler() {
        if (file.is_open()) {
            file.close();
        }
    }

private:
    std::ifstream file;
};

bool argParse(int argc, char *argv[], FileHandler &dirs_file, FileHandler &titles_file, FileHandler &akas_file,
              std::string &dirs_name);

bool getNameRow(std::ifstream &file, std::vector<std::string> &row);

bool getTitleRow(std::ifstream &file, std::vector<std::string> &row);

bool getAkasRow(std::ifstream &file, std::vector<std::string> &row);

bool checkNameFields(const std::vector<std::string> &buf);

bool checkTitleFields(const std::vector<std::string> &buf);

bool checkAkasFields(const std::vector<std::string> &buf);

bool sortNamesTconst(const std::vector<std::string> &names, std::vector<std::string> &to);

bool findDirector(std::ifstream &file, std::vector<std::string> &row, const std::string &dirs_name);

bool findTitles(std::ifstream &file, std::vector<std::string> &row, std::vector<std::string> &titles);

std::vector<std::string> findRusTitles(std::ifstream &file, std::vector<std::string> &row,
                                       const std::vector<std::string> &titles);
