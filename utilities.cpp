#include <iostream>
#include "vector"

#include "utilities.hpp"

using namespace std;


int get_name_row(ifstream &file, vector<string> &row) {
    if (row.size() != NAME_ROW_LENGTH) {
        cerr << "Names row must be length " << NAME_ROW_LENGTH << endl;
        return -1;
    }
    if (file.eof()) {
        cerr << "Function get_name_row reached the eof\n";
        return -1;
    }
    string line, buf;
    getline(file, line);
    int count = 0;
    for (char i : line) {
        if (i != '\t') {
            buf += i;
        } else if (count<row.size()) {
            row[count++] = buf;
            buf.clear();
        }
    }
    if (!buf.empty()) {
        row[count++] = buf;
    }
    if (count != row.size()) {
        cerr << "Invalid name row\n";
        return -1;
    }
    return 0;
}

int get_title_row(ifstream &file, vector<string> &row) {
    if (row.size() != TITLE_ROW_LENGTH) {
        cerr << "Titles row must be length " << TITLE_ROW_LENGTH << endl;
        return -1;
    }
    if (file.eof()) {
        cerr << "Function get_title_row reached the eof\n";
        return -1;
    }
    string line, buf;
    getline(file, line);
    int count = 0;
    for (char i : line) {
        if (i != '\t') {
            buf += i;
        } else if (count<row.size()) {
            row[count++] = buf;
            buf.clear();
        }
    }
    if (!buf.empty()) {
        row[count++] = buf;
    }
    if (count != row.size()) {
        cerr << "Invalid titles row\n";
        return -1;
    }
    return 0;
}

int get_akas_row(ifstream &file, vector<string> &row) {
    if (row.size() != AKAS_ROW_LENGTH) {
        cerr << "akas row must be length " << AKAS_ROW_LENGTH << endl;
        return -1;
    }
    if (file.eof()) {
        cerr << "Function get_akas_row reached the eof\n";
        return -1;
    }
    string line, buf;
    getline(file, line);
    int count = 0;
    for (char i : line) {
        if (i != '\t') {
            buf += i;
        } else if (count<row.size()) {
            row[count++] = buf;
            buf.clear();
        }
    }
    if (!buf.empty()) {
        row[count++] = buf;
    }
    if (count != row.size()) {
        cerr << "Invalid akas row\n";
        return -1;
    }
    return 0;
}

int check_name_fields(const vector<string> &buf) {
    vector<string> agent = {
            "nconst",
            "primaryName",
            "birthYear",
            "deathYear",
            "primaryProfession",
            "knownForTitles"
    };
    if (buf != agent) {
        return -1;
    }
    return 0;
}

int check_title_fields(const vector<string> &buf) {
    vector<string> agent = {
            "tconst",
            "titleType",
            "primaryTitle",
            "originalTitle",
            "isAdult",
            "startYear",
            "endYear",
            "runtimeMinutes",
            "genres"
    };
    if (buf != agent) {
        return -1;
    }
    return 0;
}

int check_akas_fields(const vector<string> &buf) {
    vector<string> agent = {
            "titleId",
            "ordering",
            "title",
            "region",
            "language",
            "types",
            "attributes",
            "isOriginalTitle"
    };
    if (buf != agent) {
        return -1;
    }
    return 0;
}

int sort_names_tconst(const vector<string> &names, vector<string> &to) {
    if (names.size() != NAME_ROW_LENGTH) {
        cerr << "Names row must be length " << NAME_ROW_LENGTH << endl;
        return -1;
    }

    while (names[5].find("tt", to.size()*(TCONST_NUM_LENGTH+2)) != string::npos) {
        to.push_back(names[5].substr(names[5].find("tt", to.size()*(TCONST_NUM_LENGTH+2)), TCONST_NUM_LENGTH+2));
    }
    sort(to.begin(), to.end());

    return 0;
}
