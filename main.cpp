#include <iostream>
#include <fstream>
#include "vector"

using namespace std;

int get_name_row(ifstream &file, vector<string> &buf) {
    if (buf.size() != 6) {
        cerr << "Name row buffer must be length 6\n";
        return -1;
    }
    string test;
    for (auto & i : buf) {
        if (file.eof()) {
            cerr << "Function get_name_row reached the eof\n";
            return -1;
        }
        file >> i;
    }
    return 0;
}

int get_title_row(ifstream &file, vector<string> &buf) {
    if (buf.size() != 9) {
        cerr << "Name row buffer must be length 6\n";
        return -1;
    }
    string test;
    for (auto & i : buf) {
        if (file.eof()) {
            cerr << "Function get_name_row reached the eof\n";
            return -1;
        }
        file >> i;
    }
    return 0;
}

int check_name_fields(vector<string> buf) {
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

int check_title_fields(vector<string> buf) {
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

int main(int argc, char *argv[]) {
    // Argument parsing
    // -d /path/to/directors.csv     path to file with directors names
    // -t /path/to/titles.csv        path to file with titles
    // -n "Directors name"           directors name to search films
    if (argc < 7) {
        cerr << "Not enough arguments\n";
        return EXIT_FAILURE;
    }
    ifstream dirs_file;
    ifstream titles_file;
    string dirs_name;
    for (int i=1; i<argc;) {
        if (argv[i][0] != '-') {
            cerr << "Invalid argument\n";
            return EXIT_FAILURE;
        }

        if (argv[i][1] == 'd') {
            dirs_file.open(argv[i + 1], ios::in);
            if (!dirs_file.is_open()) {
                cerr << "Invalid path\n";
                return EXIT_FAILURE;
            }
            i += 2;
        } else if (argv[i][1] == 't') {
            titles_file.open(argv[i+1], ios::in);
            if (!titles_file.is_open()) {
                cerr << "Invalid path\n";
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

    vector<string> name_row(6);
    get_name_row(dirs_file, name_row);
    cout << "\nTest\n" << check_name_fields(name_row);

    vector<string> title_row(9);
    get_title_row(titles_file, title_row);
    cout << "\nTest\n" << check_title_fields(title_row);

    dirs_file.close();
    titles_file.close();
    return EXIT_SUCCESS;
}
