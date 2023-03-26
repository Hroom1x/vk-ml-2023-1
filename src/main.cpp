#include "utilities.hpp"


int main(int argc, char *argv[]) {

    // -d /path/to/name.basics.tsv       path to file with directors names
    // -t /path/to/titles.basics.tsv     path to file with titles
    // -a /path/to/titles.akas.tsv       path to file with titles localization
    // -n "Directors name"               directors name to search films
    // === Example ===
    // -d /home/hrmx/Desktop/name.basics.tsv -t /home/hrmx/Desktop/title.basics.tsv -a /home/hrmx/Desktop/title.akas.tsv -n "Aleksey Balabanov"

    FileHandler dirs_file;
    FileHandler titles_file;
    FileHandler akas_file;
    std::string dirs_name;

    if (argParse(argc, argv, dirs_file, titles_file, akas_file, dirs_name)) {
        return ERR_ARGS_PARSING;
    }

    std::vector<std::string> name_row(NAME_ROW_LENGTH);
    std::vector<std::string> title_row(TITLE_ROW_LENGTH);
    std::vector<std::string> akas_row(AKAS_ROW_LENGTH);
    if (getNameRow(dirs_file._file, name_row) ||
        getTitleRow(titles_file._file, title_row) ||
        getAkasRow(akas_file._file, akas_row)) {
        return ERR_INVALID_ROW;
    }


    // Checking format of first row in files
    if (checkNameFields(name_row)) {
        std::cerr << "Invalid column titles in names file" << std::endl;
        return ERR_INVALID_FIRST_ROW;
    }
    if (checkTitleFields(title_row)) {
        std::cerr << "Invalid column titles in titles file" << std::endl;
        return ERR_INVALID_FIRST_ROW;
    }
    if (checkAkasFields(akas_row)) {
        std::cerr << "Invalid column titles in akas file" << std::endl;
        return ERR_INVALID_FIRST_ROW;
    }

    // Searching for given director
    std::vector<std::string> titles;
    if (!findDirector(dirs_file._file, name_row, dirs_name)) {
        sortNamesTconst(name_row, titles);
    } else {
        std::cerr << "Given director is not found" << std::endl;
        return ERR_NOT_FOUND;
    }

    // Searching for given titles and remove not suitable
    if (findTitles(titles_file._file, title_row, titles)) {
        std::cerr << "Given titles are not found" << std::endl;
        return ERR_NOT_FOUND;
    }

    // Searching for russian titles
    std::vector<std::string> rus_titles = findRusTitles(akas_file._file, akas_row, titles);
    if (rus_titles.empty()) {
        std::cout << "Titles on russian not found" << std::endl;
    } else for (std::string &title : rus_titles) {
        std::cout << title << std::endl;
    }

    return EXIT_SUCCESS;
}
