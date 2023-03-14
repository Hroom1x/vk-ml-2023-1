#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char *argv[]) {
    FILE *directors_file = nullptr;
    FILE *titles_file = nullptr;

    // Argument parsing
    // -d /path/to/directors.csv     path to file with directors names
    // -t /path/to/titles.csv        path to file with titles
    for (int i=1; i<argc;) {
        if (argv[i][0] != '-') {
            fprintf(stderr, "Invalid argument\n");
            return EXIT_FAILURE;
        }

        if (argv[i][1] == 'd') {
            directors_file = fopen(argv[i+1], "r");
            if (directors_file == nullptr) {
                fprintf(stderr, "Invalid path\n");
                return EXIT_FAILURE;
            }
            i += 2;
        } else if (argv[i][1] == 't') {
            titles_file = fopen(argv[i+1], "r");
            if (titles_file == nullptr) {
                fprintf(stderr, "Invalid path\n");
                return EXIT_FAILURE;
            }
            i += 2;
        } else {
            fprintf(stderr, "Unknown flag\n");
            return EXIT_FAILURE;
        }
    }

    if (directors_file) fclose(directors_file);
    if (titles_file) fclose(titles_file);
    return EXIT_SUCCESS;
}
