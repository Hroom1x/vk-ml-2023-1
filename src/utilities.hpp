#pragma once

#include <fstream>
#include <vector>

#define NAME_ROW_LENGTH 6
#define TITLE_ROW_LENGTH 9
#define AKAS_ROW_LENGTH 8
#define ARG_NUMBER 7
#define TCONST_NUM_LENGTH 7


int get_name_row(std::ifstream &file, std::vector<std::string> &row);

int get_title_row(std::ifstream &file, std::vector<std::string> &row);

int get_akas_row(std::ifstream &file, std::vector<std::string> &row);

int check_name_fields(const std::vector<std::string> &buf);

int check_title_fields(const std::vector<std::string> &buf);

int check_akas_fields(const std::vector<std::string> &buf);

int sort_names_tconst(const std::vector<std::string> &names, std::vector<std::string> &to);

int find_director(std::ifstream &file, std::vector<std::string> &row, const std::string &dirs_name);

int find_titles(std::ifstream &file, std::vector<std::string> &row, std::vector<std::string> &titles);

std::vector<std::string> find_rus_titles(std::ifstream &file, std::vector<std::string> &row, const std::vector<std::string> &titles);
