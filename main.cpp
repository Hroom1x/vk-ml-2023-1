#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char *argv[]) {
    ifstream directors_file;
    ifstream titles_file;

    // Argument parsing
    // -d /path/to/directors.csv     path to file with directors names
    // -t /path/to/titles.csv        path to file with titles
    if (argc < 5) {
        cerr << "Not enough arguments\n";
        return EXIT_FAILURE;
    }
    for (int i=1; i<argc;) {
        if (argv[i][0] != '-') {
            cerr << "Invalid argument\n";
            return EXIT_FAILURE;
        }

        if (argv[i][1] == 'd') {
            directors_file.open(argv[i+1], ios::in);
            if (!directors_file.is_open()) {
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
        } else {
            cerr << "Unknown flag\n";
            return EXIT_FAILURE;
        }
    }

    directors_file.close();
    titles_file.close();
    return EXIT_SUCCESS;
}
