#include <iostream>
#include <fstream>
#include "vector"
#include <algorithm>

#define NAME_ROW_LENGTH 6
#define TITLE_ROW_LENGTH 9
#define akas_ROW_LENGTH 8
#define ARG_NUMBER 7
#define TCONST_NUM_LENGTH 7

using namespace std;


int get_name_row(ifstream &file, vector<string> &row) {
    if (row.size() != NAME_ROW_LENGTH) {
        cerr << "Names row must be length " << NAME_ROW_LENGTH << endl;
        return -1;
    }
    if (file.eof()) {
        cerr << "Function get_name_row reached the eof\n";
        return -1;
    }
    string line, buf;
    getline(file, line);
    int count = 0;
    for (char i : line) {
        if (i != '\t') {
            buf += i;
        } else if (count<row.size()) {
            row[count++] = buf;
            buf.clear();
        }
    }
    if (!buf.empty()) {
        row[count++] = buf;
    }
    if (count != row.size()) {
        cerr << "Invalid name row\n";
        return -1;
    }
    return 0;
}

int get_title_row(ifstream &file, vector<string> &row) {
    if (row.size() != TITLE_ROW_LENGTH) {
        cerr << "Titles row must be length " << TITLE_ROW_LENGTH << endl;
        return -1;
    }
    if (file.eof()) {
        cerr << "Function get_title_row reached the eof\n";
        return -1;
    }
    string line, buf;
    getline(file, line);
    int count = 0;
    for (char i : line) {
        if (i != '\t') {
            buf += i;
        } else if (count<row.size()) {
            row[count++] = buf;
            buf.clear();
        }
    }
    if (!buf.empty()) {
        row[count++] = buf;
    }
    if (count != row.size()) {
        cerr << "Invalid titles row\n";
        return -1;
    }
    return 0;
}

int get_akas_row(ifstream &file, vector<string> &row) {
    if (row.size() != akas_ROW_LENGTH) {
        cerr << "akas row must be length " << akas_ROW_LENGTH << endl;
        return -1;
    }
    if (file.eof()) {
        cerr << "Function get_akas_row reached the eof\n";
        return -1;
    }
    string line, buf;
    getline(file, line);
    int count = 0;
    for (char i : line) {
        if (i != '\t') {
            buf += i;
        } else if (count<row.size()) {
            row[count++] = buf;
            buf.clear();
        }
    }
    if (!buf.empty()) {
        row[count++] = buf;
    }
    if (count != row.size()) {
        cerr << "Invalid akas row\n";
        return -1;
    }
    return 0;
}

int check_name_fields(const vector<string> &buf) {
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

int check_title_fields(const vector<string> &buf) {
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

int check_akas_fields(const vector<string> &buf) {
    vector<string> agent = {
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

int tconst_to_int(const string &s, int pos) {
    int res = 0;
    if (s.find("tt", pos) != string::npos) {
        res = stoi(s.substr(s.find("tt", pos)+2, TCONST_NUM_LENGTH));
    }
    if (res == 0) {
        cerr << "Warning: tconst_to_int return 0\n";
    }
    return res;
}

string int_to_tconst(const int a) {
    int power = 10;
    string res = "tt";
    for (int i=1; i<TCONST_NUM_LENGTH; i++) {
        if (a%power == a) {
            res.insert(res.end(), TCONST_NUM_LENGTH-i, '0');
            res.append(to_string(a));
            return res;
        }
        power*=10;
    }
    return "";
}

int sort_names_tconst(const vector<string> &names, vector<string> &to) {
    if (names.size() != NAME_ROW_LENGTH) {
        cerr << "Names row must be length " << NAME_ROW_LENGTH << endl;
        return -1;
    }

    while (names[5].find("tt", to.size()*(TCONST_NUM_LENGTH+2)) != string::npos) {
        to.push_back(names[5].substr(names[5].find("tt", to.size()*(TCONST_NUM_LENGTH+2)), TCONST_NUM_LENGTH+2));
    }
    sort(to.begin(), to.end());

    return 0;
}

bool is_russian_title(const string &s) {
    if (s.size() < 2) {
        cerr << "Function is_russian_title got string with size < 2\n";
        return false;
    }
    for (int i=1; i<s.size(); i++) {
        if (s[i-1] >= 32 && s[i-1] <= 64) {
            // Chars [32; 64] can be found in title with any language
            continue;
        }
        if (s[i-1] != -47 && s[i-1] != -48) {
            // First char of cyrillic symbol is -47 or -48
            return false;
        }
        if (s[i] >= -128 && s[i] <= -65) {
            // Cyrillic symbol found
            i++;
            continue;
        } else {
            return false;
        }
    }
    return true;
}

// String that contains all whitelist symbols
// " !\"#$%&'()*+,-./0123456789:;<=>?@абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
int main(int argc, char *argv[]) {
    /*string test = " !\"#$%&'()*+,-./0123456789:;<=>?@абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    cout << is_russian_title(test);
    return EXIT_SUCCESS;*/

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
    vector<string> akas_row(akas_ROW_LENGTH);
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
    while (!dirs_file.eof()) {
        if (get_name_row(dirs_file, name_row)) {
            dirs_file.close();
            titles_file.close();
            return EXIT_FAILURE;
        }
        if (name_row[1] == dirs_name) {
            if (name_row[4].find("director") == string::npos) {
                cerr << "Given person never have been director\n";
                dirs_file.close();
                titles_file.close();
                return EXIT_FAILURE;
            }
            // If found
            sort_names_tconst(name_row, titles);
            dirs_file.close();
            break;
        }
    }

    // Searching for given titles and remove not suitable
    {
        int count = 0;
        while (!titles_file.eof() && count<titles.size()) {
            get_title_row(titles_file, title_row);

            // We suppose that file with titles sorted by ids and have given titles
            if (title_row[0] == titles[count]) {
                if (title_row[4] != "0" || title_row[1] != "movie") {
                    titles.erase(titles.begin()+count);
                    count--;
                }
                count++;
            }
        }
        titles_file.close();
    }

    // Searching for russian titles
    {
        int count = 0;
        vector<string> titles_with_rus_chars;
        while (!akas_file.eof() && count<titles.size()) {
            get_akas_row(akas_file, akas_row);
            if (akas_row[0] == titles[count]) {
                while (akas_row[0] == titles[count] && !akas_file.eof()) {
                    get_akas_row(akas_file, akas_row);
                    if (akas_row[3] == "RU" || akas_row[3] == "ru") {
                        titles_with_rus_chars.push_back(akas_row[2]);
                    }
                }
                count++;
            }
        }
        if (titles_with_rus_chars.empty()) {
            cout << "Titles on russian not found\n";
        } else for (string &title : titles_with_rus_chars) {
            cout << title << endl;
        }
        akas_file.close();
    }

    dirs_file.close();
    titles_file.close();
    akas_file.close();
    return EXIT_SUCCESS;
}
