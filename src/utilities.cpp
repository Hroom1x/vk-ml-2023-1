#include <iostream>
#include <vector>

#include "utilities.hpp"


int get_name_row(std::ifstream &file, std::vector<std::string> &row) {
    if (row.size() != NAME_ROW_LENGTH) {
        std::cerr << "Names row must be length " << NAME_ROW_LENGTH << std::endl;
        return -1;
    }
    if (file.eof()) {
        std::cerr << "Function get_name_row reached the eof\n";
        return -1;
    }
    std::string line, buf;
    getline(file, line);
    int count = 0;
    for (char i : line) {
        if (i != '\t') {
            buf += i;
        } else if (count<int(row.size())) {
            row[count++] = buf;
            buf.clear();
        }
    }
    if (!buf.empty()) {
        row[count++] = buf;
    }
    if (count != int(row.size())) {
        std::cerr << "Invalid name row\n";
        return -1;
    }
    return 0;
}

int get_title_row(std::ifstream &file, std::vector<std::string> &row) {
    if (row.size() != TITLE_ROW_LENGTH) {
        std::cerr << "Titles row must be length " << TITLE_ROW_LENGTH << std::endl;
        return -1;
    }
    if (file.eof()) {
        std::cerr << "Function get_title_row reached the eof\n";
        return -1;
    }
    std::string line, buf;
    getline(file, line);
    int count = 0;
    for (char i : line) {
        if (i != '\t') {
            buf += i;
        } else if (count<int(row.size())) {
            row[count++] = buf;
            buf.clear();
        }
    }
    if (!buf.empty()) {
        row[count++] = buf;
    }
    if (count != int(row.size())) {
        std::cerr << "Invalid titles row\n";
        return -1;
    }
    return 0;
}

int get_akas_row(std::ifstream &file, std::vector<std::string> &row) {
    if (row.size() != AKAS_ROW_LENGTH) {
        std::cerr << "Akas row must be length " << AKAS_ROW_LENGTH << std::endl;
        return -1;
    }
    if (file.eof()) {
        std::cerr << "Function get_akas_row reached the eof\n";
        return -1;
    }
    std::string line, buf;
    getline(file, line);
    int count = 0;
    for (char i : line) {
        if (i != '\t') {
            buf += i;
        } else if (count<int(row.size())) {
            row[count++] = buf;
            buf.clear();
        }
    }
    if (!buf.empty()) {
        row[count++] = buf;
    }
    if (count != int(row.size())) {
        std::cerr << "Invalid akas row\n";
        return -1;
    }
    return 0;
}

int check_name_fields(const std::vector<std::string> &buf) {
    std::vector<std::string> agent = {
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

int check_title_fields(const std::vector<std::string> &buf) {
    std::vector<std::string> agent = {
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

int check_akas_fields(const std::vector<std::string> &buf) {
    std::vector<std::string> agent = {
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

int sort_names_tconst(const std::vector<std::string> &names, std::vector<std::string> &to) {
    if (names.size() != NAME_ROW_LENGTH) {
        std::cerr << "Names row must be length " << NAME_ROW_LENGTH << std::endl;
        return -1;
    }

    while (names[5].find("tt", to.size()*(TCONST_NUM_LENGTH+2)) != std::string::npos) {
        to.push_back(names[5].substr(names[5].find("tt", to.size()*(TCONST_NUM_LENGTH+2)), TCONST_NUM_LENGTH+2));
    }
    sort(to.begin(), to.end());

    return 0;
}

int find_director(std::ifstream &file, std::vector<std::string> &row, const std::string &dirs_name) {
    while (!file.eof()) {
        if (get_name_row(file, row)) {
            return -1;
        }
        if (row[1] == dirs_name) {
            if (row[4].find("director") == std::string::npos) {
                std::cerr << "Given person never have been director\n";
                return -1;
            }
            return 0;
        }
    }
    std::cerr << "Person not found\n";
    return -1;
}

int find_titles(std::ifstream &file, std::vector<std::string> &row, std::vector<std::string> &titles) {
    int count = 0;
    while (count<int(titles.size()) && !file.eof()) {
        get_title_row(file, row);

        // We suppose that file with titles sorted by ids and have given titles
        if (row[0] == titles[count]) {
            if (row[4] != "0" || row[1] != "movie") {
                titles.erase(titles.begin()+count);
                count--;
            }
            count++;
        }
    }
    if (count == 0) {
        return -1;
    }
    return 0;
}

std::vector<std::string> find_rus_titles(std::ifstream &file, std::vector<std::string> &row, const std::vector<std::string> &titles)  {
    std::vector<std::string> rus_titles;
    int count = 0;
    while (count<int(titles.size()) && !file.eof()) {
        get_akas_row(file, row);
        if (row[0] == titles[count]) {
            while (row[0] == titles[count] && !file.eof()) {
                get_akas_row(file, row);
                std::transform(row[3].begin(), row[3].end(), row[3].begin(),
                               [](unsigned char c){ return std::tolower(c); });
                if (row[3] == "ru") {
                    rus_titles.push_back(row[2]);
                }
            }
            count++;
        }
    }
    return rus_titles;
}
