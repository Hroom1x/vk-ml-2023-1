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


bool arg_parse(int argc, char *argv[], std::ifstream &dirs_file, std::ifstream &titles_file, std::ifstream &akas_file,
               std::string &dirs_name);

bool get_name_row(std::ifstream &file, std::vector<std::string> &row);

bool get_title_row(std::ifstream &file, std::vector<std::string> &row);

bool get_akas_row(std::ifstream &file, std::vector<std::string> &row);

bool check_name_fields(const std::vector<std::string> &buf);

bool check_title_fields(const std::vector<std::string> &buf);

bool check_akas_fields(const std::vector<std::string> &buf);

bool sort_names_tconst(const std::vector<std::string> &names, std::vector<std::string> &to);

bool find_director(std::ifstream &file, std::vector<std::string> &row, const std::string &dirs_name);

bool find_titles(std::ifstream &file, std::vector<std::string> &row, std::vector<std::string> &titles);

std::vector<std::string> find_rus_titles(std::ifstream &file, std::vector<std::string> &row, const std::vector<std::string> &titles);
