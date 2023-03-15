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
    for (int i=0; i<6; i++) {
        if (file.eof()) {
            cerr << "Function get_name_row reached the eof\n";
            return -1;
        }
        file >> test;
        cout << endl;
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

    vector<string> row(6);
    get_name_row(dirs_file, row);

    /*
    string buf;
    while (true) {
        cin >> buf;
        getline(dirs_file, buf);
        cout << buf;
    }
     */

    dirs_file.close();
    titles_file.close();
    return EXIT_SUCCESS;
}
