#include <iostream>
#include "vector"
#include "utilities.hpp"

using namespace std;


int main(int argc, char *argv[]) {
    // Argument parsing
    // -d /path/to/name.basics.tsv       path to file with directors names
    // -t /path/to/titles.basics.tsv     path to file with titles
    // -a /path/to/titles.akas.tsv       path to file with titles localization
    // -n "Directors name"               directors name to search films
    if (argc < ARG_NUMBER) {
        cerr << "Not enough arguments\n";
        return EXIT_FAILURE;
    }
    ifstream dirs_file;
    ifstream titles_file;
    ifstream akas_file;
    string dirs_name;
    for (int i=1; i<argc;) {
        if (argv[i][0] != '-') {
            cerr << "Invalid argument\n";
            return EXIT_FAILURE;
        }

        if (argv[i][1] == 'd') {
            dirs_file.open(argv[i + 1], ios::in);
            if (!dirs_file.is_open()) {
                cerr << "Invalid path to directors names\n";
                return EXIT_FAILURE;
            }
            i += 2;
        } else if (argv[i][1] == 't') {
            titles_file.open(argv[i+1], ios::in);
            if (!titles_file.is_open()) {
                cerr << "Invalid path to titles\n";
                return EXIT_FAILURE;
            }
            i += 2;
        } else if (argv[i][1] == 'a') {
            akas_file.open(argv[i+1], ios::in);
            if (!akas_file.is_open()) {
                cerr << "Invalid path to akas\n";
                return EXIT_FAILURE;
            }
            i += 2;
        } else if (argv[i][1] == 'n') {
            dirs_name = argv[i+1];
            i += 2;
        } else {
            cerr << "Unknown flag\n";
            return EXIT_FAILURE;
        }
    }

    vector<string> name_row(NAME_ROW_LENGTH);
    vector<string> title_row(TITLE_ROW_LENGTH);
    vector<string> akas_row(AKAS_ROW_LENGTH);
    get_name_row(dirs_file, name_row);
    get_title_row(titles_file, title_row);
    get_akas_row(akas_file, akas_row);

    // Checking format of first row in files
    if (check_name_fields(name_row)) {
        cerr << "Invalid column titles in names file\n";
        return EXIT_FAILURE;
    }
    if (check_title_fields(title_row)) {
        cerr << "Invalid column titles in titles file\n";
        return EXIT_FAILURE;
    }
    if (check_akas_fields(akas_row)) {
        cerr << "Invalid column titles in akas file\n";
        return EXIT_FAILURE;
    }

    // Searching for given director
    vector<string> titles;
    if (!find_director(dirs_file, name_row, dirs_name)) {
        sort_names_tconst(name_row, titles);
        dirs_file.close();
    } else {
        cerr << "Given director is not found\n";
        dirs_file.close();
        titles_file.close();
        akas_file.close();
        return EXIT_FAILURE;
    }

    // Searching for given titles and remove not suitable
    if (!find_titles(titles_file, title_row, titles)) {
        titles_file.close();
    } else {
        cerr << "Given titles are not found\n";
        dirs_file.close();
        titles_file.close();
        akas_file.close();
        return EXIT_FAILURE;
    }

    // Searching for russian titles
    vector<string> rus_titles = find_rus_titles(akas_file, akas_row, titles);
    if (rus_titles.empty()) {
        cout << "Titles on russian not found\n";
    } else for (string &title : rus_titles) {
        cout << title << endl;
    }

    dirs_file.close();
    titles_file.close();
    akas_file.close();
    return EXIT_SUCCESS;
}
