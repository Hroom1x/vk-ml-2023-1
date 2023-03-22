#include "../include/utilities.hpp"


bool argParse(int argc, char *argv[], std::ifstream &dirs_file, std::ifstream &titles_file, std::ifstream &akas_file,
              std::string &dirs_name) {
    if (argc < ARG_NUMBER) {
        std::cerr << "Not enough arguments" << std::endl;
        return true;
    }
    if (argc > ARG_NUMBER) {
        std::cerr << "Too many arguments" << std::endl;
        return true;
    }

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-d") {
            dirs_file.open(argv[++i], std::ios::in);
            if (!dirs_file.is_open()) {
                std::cerr << "Invalid path to directors names" << std::endl;
                return true;
            }
        } else if (std::string(argv[i]) == "-t") {
            titles_file.open(argv[++i], std::ios::in);
            if (!titles_file.is_open()) {
                std::cerr << "Invalid path to titles" << std::endl;
                return true;
            }
        } else if (std::string(argv[i]) == "-a") {
            akas_file.open(argv[++i], std::ios::in);
            if (!akas_file.is_open()) {
                std::cerr << "Invalid path to akas" << std::endl;
                return true;
            }
        } else if (std::string(argv[i]) == "-n") {
            dirs_name = argv[++i];
        } else {
            std::cerr << "Unknown flag" << std::endl;
            return true;
        }
    }

    return false;
}

bool getNameRow(std::ifstream &file, std::vector<std::string> &row) {
    if (row.size() != NAME_ROW_LENGTH) {
        std::cerr << "Names row must be length " << NAME_ROW_LENGTH << std::endl;
        return true;
    }
    if (file.eof()) {
        std::cerr << "Function getNameRow reached the eof" << std::endl;
        return true;
    }
    std::string line, buf;
    getline(file, line);
    size_t count = 0;
    for (char i : line) {
        if (i != '\t') {
            buf += i;
        } else if (count < row.size()) {
            row[count++] = buf;
            buf.clear();
        }
    }
    if (!buf.empty()) {
        row[count++] = buf;
    }
    if (count != row.size()) {
        std::cerr << "Invalid name row" << std::endl;
        return true;
    }
    return false;
}

bool getTitleRow(std::ifstream &file, std::vector<std::string> &row) {
    if (row.size() != TITLE_ROW_LENGTH) {
        std::cerr << "Titles row must be length " << TITLE_ROW_LENGTH << std::endl;
        return true;
    }
    if (file.eof()) {
        std::cerr << "Function getTitleRow reached the eof" << std::endl;
        return true;
    }
    std::string line, buf;
    getline(file, line);
    size_t count = 0;
    for (char i : line) {
        if (i != '\t') {
            buf += i;
        } else if (count < row.size()) {
            row[count++] = buf;
            buf.clear();
        }
    }
    if (!buf.empty()) {
        row[count++] = buf;
    }
    if (count != row.size()) {
        std::cerr << "Invalid titles row" << std::endl;
        return true;
    }
    return false;
}

bool getAkasRow(std::ifstream &file, std::vector<std::string> &row) {
    if (row.size() != AKAS_ROW_LENGTH) {
        std::cerr << "Akas row must be length " << AKAS_ROW_LENGTH << std::endl;
        return true;
    }
    if (file.eof()) {
        std::cerr << "Function getAkasRow reached the eof" << std::endl;
        return true;
    }
    std::string line, buf;
    getline(file, line);
    size_t count = 0;
    for (char i : line) {
        if (i != '\t') {
            buf += i;
        } else if (count < row.size()) {
            row[count++] = buf;
            buf.clear();
        }
    }
    if (!buf.empty()) {
        row[count++] = buf;
    }
    if (count != row.size()) {
        std::cerr << "Invalid akas row" << std::endl;
        return true;
    }
    return false;
}

bool checkNameFields(const std::vector<std::string> &buf) {
    std::vector<std::string> agent = {
            "nconst",
            "primaryName",
            "birthYear",
            "deathYear",
            "primaryProfession",
            "knownForTitles"
    };
    if (buf != agent) {
        return true;
    }
    return false;
}

bool checkTitleFields(const std::vector<std::string> &buf) {
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
        return true;
    }
    return false;
}

bool checkAkasFields(const std::vector<std::string> &buf) {
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
        return true;
    }
    return false;
}

bool sortNamesTconst(const std::vector<std::string> &names, std::vector<std::string> &to) {
    if (names.size() != NAME_ROW_LENGTH) {
        std::cerr << "Names row must be length " << NAME_ROW_LENGTH << std::endl;
        return true;
    }

    while (names[5].find("tt", to.size()*(TCONST_NUM_LENGTH+2)) != std::string::npos) {
        to.push_back(names[5].substr(names[5].find("tt", to.size()*(TCONST_NUM_LENGTH+2)),
                                     TCONST_NUM_LENGTH+2));
    }
    std::sort(to.begin(), to.end());

    return false;
}

bool findDirector(std::ifstream &file, std::vector<std::string> &row, const std::string &dirs_name) {
    while (!file.eof()) {
        if (getNameRow(file, row)) {
            return true;
        }
        if (row[1] == dirs_name) {
            if (row[4].find("director") == std::string::npos) {
                std::cerr << "Given person never have been director" << std::endl;
                return true;
            }
            return false;
        }
    }
    std::cerr << "Person not found" << std::endl;
    return true;
}

bool findTitles(std::ifstream &file, std::vector<std::string> &row, std::vector<std::string> &titles) {
    size_t count = 0;
    while (count < titles.size() && !file.eof()) {
        getTitleRow(file, row);

        // We suppose that file with titles sorted by ids and have given titles
        if (row[0] == titles[count]) {
            if (row[4] != "0" || row[1] != "movie") {
                titles.erase(titles.begin() + count);
                count--;
            }
            count++;
        }
    }
    if (count == 0) {
        return true;
    }
    return false;
}

std::vector<std::string> findRusTitles(std::ifstream &file, std::vector<std::string> &row,
                                       const std::vector<std::string> &titles)  {
    std::vector<std::string> rus_titles;
    size_t count = 0;
    while (count < titles.size() && !file.eof()) {
        getAkasRow(file, row);
        if (row[0] == titles[count]) {
            while (row[0] == titles[count] && !file.eof()) {
                getAkasRow(file, row);
                if (std::tolower(row[3][0]) == 'r' && std::tolower(row[3][1]) == 'u') {
                    rus_titles.push_back(row[2]);
                }
            }
            ++count;
        }
    }
    return rus_titles;
}
