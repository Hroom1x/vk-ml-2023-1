#ifndef HOMEWORK_UTILITIES_HPP
#define HOMEWORK_UTILITIES_HPP

#include <fstream>
#include "vector"

#define NAME_ROW_LENGTH 6
#define TITLE_ROW_LENGTH 9
#define AKAS_ROW_LENGTH 8
#define ARG_NUMBER 7
#define TCONST_NUM_LENGTH 7

using namespace std;


int get_name_row(ifstream &file, vector<string> &row);

int get_title_row(ifstream &file, vector<string> &row);

int get_akas_row(ifstream &file, vector<string> &row);

int check_name_fields(const vector<string> &buf);

int check_title_fields(const vector<string> &buf);

int check_akas_fields(const vector<string> &buf);

int sort_names_tconst(const vector<string> &names, vector<string> &to);

int find_director(ifstream &file, vector<string> &row, const string &dirs_name);

int find_titles(ifstream &file, vector<string> &row, vector<string> &titles);

vector<string> find_rus_titles(ifstream &file, vector<string> &row, const vector<string> &titles);

#endif  // HOMEWORK_UTILITIES_HPP
