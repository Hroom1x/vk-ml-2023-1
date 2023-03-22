#include <iostream>
#include <vector>
#include "utilities.hpp"


int main(int argc, char *argv[]) {
    // Argument parsing
    // -d /path/to/name.basics.tsv       path to file with directors names
    // -t /path/to/titles.basics.tsv     path to file with titles
    // -a /path/to/titles.akas.tsv       path to file with titles localization
    // -n "Directors name"               directors name to search films
    if (argc < ARG_NUMBER) {
        std::cerr << "Not enough arguments" << std::endl;
        return EXIT_FAILURE;
    }
    std::ifstream dirs_file;
    std::ifstream titles_file;
    std::ifstream akas_file;
    std::string dirs_name;
    for (size_t i=1; i<argc;) {
        if (argv[i][0] != '-') {
            std::cerr << "Invalid argument" << std::endl;
            return EXIT_FAILURE;
        }

        if (argv[i][1] == 'd') {
            dirs_file.open(argv[i + 1], std::ios::in);
            if (!dirs_file.is_open()) {
                std::cerr << "Invalid path to directors names" << std::endl;
                return EXIT_FAILURE;
            }
            i += 2;
        } else if (argv[i][1] == 't') {
            titles_file.open(argv[i+1], std::ios::in);
            if (!titles_file.is_open()) {
                std::cerr << "Invalid path to titles" << std::endl;
                return EXIT_FAILURE;
            }
            i += 2;
        } else if (argv[i][1] == 'a') {
            akas_file.open(argv[i+1], std::ios::in);
            if (!akas_file.is_open()) {
                std::cerr << "Invalid path to akas" << std::endl;
                return EXIT_FAILURE;
            }
            i += 2;
        } else if (argv[i][1] == 'n') {
            dirs_name = argv[i+1];
            i += 2;
        } else {
            std::cerr << "Unknown flag" << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::vector<std::string> name_row(NAME_ROW_LENGTH);
    std::vector<std::string> title_row(TITLE_ROW_LENGTH);
    std::vector<std::string> akas_row(AKAS_ROW_LENGTH);
    get_name_row(dirs_file, name_row);
    get_title_row(titles_file, title_row);
    get_akas_row(akas_file, akas_row);

    // Checking format of first row in files
    if (check_name_fields(name_row)) {
        std::cerr << "Invalid column titles in names file" << std::endl;
        return EXIT_FAILURE;
    }
    if (check_title_fields(title_row)) {
        std::cerr << "Invalid column titles in titles file" << std::endl;
        return EXIT_FAILURE;
    }
    if (check_akas_fields(akas_row)) {
        std::cerr << "Invalid column titles in akas file" << std::endl;
        return EXIT_FAILURE;
    }

    // Searching for given director
    std::vector<std::string> titles;
    if (!find_director(dirs_file, name_row, dirs_name)) {
        sort_names_tconst(name_row, titles);
        dirs_file.close();
    } else {
        std::cerr << "Given director is not found" << std::endl;
        dirs_file.close();
        titles_file.close();
        akas_file.close();
        return EXIT_FAILURE;
    }

    // Searching for given titles and remove not suitable
    if (!find_titles(titles_file, title_row, titles)) {
        titles_file.close();
    } else {
        std::cerr << "Given titles are not found" << std::endl;
        dirs_file.close();
        titles_file.close();
        akas_file.close();
        return EXIT_FAILURE;
    }

    // Searching for russian titles
    std::vector<std::string> rus_titles = find_rus_titles(akas_file, akas_row, titles);
    if (rus_titles.empty()) {
        std::cout << "Titles on russian not found" << std::endl;
    } else for (std::string &title : rus_titles) {
        std::cout << title << std::endl;
    }

    dirs_file.close();
    titles_file.close();
    akas_file.close();
    return EXIT_SUCCESS;
}
