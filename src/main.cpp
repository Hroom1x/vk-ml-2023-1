#include "../include/utilities.hpp"


int main(int argc, char *argv[]) {

    // -d /path/to/name.basics.tsv       path to file with directors names
    // -t /path/to/titles.basics.tsv     path to file with titles
    // -a /path/to/titles.akas.tsv       path to file with titles localization
    // -n "Directors name"               directors name to search films
    // === Example ===
    // -d /home/hrmx/Desktop/name.basics.tsv -t /home/hrmx/Desktop/title.basics.tsv -a /home/hrmx/Desktop/title.akas.tsv -n "Aleksey Balabanov"

    if (argc < ARG_NUMBER) {
        std::cerr << "Not enough arguments" << std::endl;
        return EXIT_FAILURE;
    }
    /*FileHandler dirs_file;
    FileHandler titles_file;
    FileHandler akas_file;*/
    std::ifstream dirs_file;
    std::ifstream titles_file;
    std::ifstream akas_file;
    std::string dirs_name;

    if (argParse(argc, argv, dirs_file, titles_file, akas_file, dirs_name)) {
        return EXIT_FAILURE;
    }

    std::vector<std::string> name_row(NAME_ROW_LENGTH);
    std::vector<std::string> title_row(TITLE_ROW_LENGTH);
    std::vector<std::string> akas_row(AKAS_ROW_LENGTH);
    if (getNameRow(dirs_file, name_row) ||
        getTitleRow(titles_file, title_row) ||
            getAkasRow(akas_file, akas_row)) {
        return EXIT_FAILURE;
    }


    // Checking format of first row in files
    if (checkNameFields(name_row)) {
        std::cerr << "Invalid column titles in names file" << std::endl;
        return EXIT_FAILURE;
    }
    if (checkTitleFields(title_row)) {
        std::cerr << "Invalid column titles in titles file" << std::endl;
        return EXIT_FAILURE;
    }
    if (checkAkasFields(akas_row)) {
        std::cerr << "Invalid column titles in akas file" << std::endl;
        return EXIT_FAILURE;
    }

    // Searching for given director
    std::vector<std::string> titles;
    if (!findDirector(dirs_file, name_row, dirs_name)) {
        sortNamesTconst(name_row, titles);
        dirs_file.close();
    } else {
        std::cerr << "Given director is not found" << std::endl;
        dirs_file.close();
        titles_file.close();
        akas_file.close();
        return EXIT_FAILURE;
    }

    // Searching for given titles and remove not suitable
    if (!findTitles(titles_file, title_row, titles)) {
        titles_file.close();
    } else {
        std::cerr << "Given titles are not found" << std::endl;
        titles_file.close();
        akas_file.close();
        return EXIT_FAILURE;
    }

    // Searching for russian titles
    std::vector<std::string> rus_titles = findRusTitles(akas_file, akas_row, titles);
    if (rus_titles.empty()) {
        std::cout << "Titles on russian not found" << std::endl;
    } else for (std::string &title : rus_titles) {
        std::cout << title << std::endl;
    }

    akas_file.close();
    return EXIT_SUCCESS;
}
