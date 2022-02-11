/*
Arjun Srivastava
arj1@uw.edu
CSE 333
Copyright 2022 Arjun Srivastava
*/

#include <iostream>
#include <cstdlib>  // for EXIT_SUCCESS
#include <map>
#include <fstream>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ifstream;
using std::string;
using std::map;
using std::pair;
using std::for_each;


// Reads the current value from the stream into output
template <typename T>
bool ReadValue(ifstream& in, T* output);

// Accepts a map and prints the key/value pairs
void PrintOut(const pair<string, int>& p);

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Please input one .txt file argument" << endl;
        exit(EXIT_FAILURE);
    }
    string filename = argv[1];
    ifstream in;
    in.open(filename);

    if (!in.is_open() || !in.good()) {
        cerr << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }

    string data;
    map<string, int> word_occurences;

    while (!in.eof()) {
        bool read = ReadValue(in, &data);
        if (!read) {
            cerr << "Error reading from file" << endl;
            exit(EXIT_FAILURE);
        }
        if (word_occurences.count(data)) {
            word_occurences[data]++;
        } else {
            word_occurences[data] = 1;
        }
    }
    in.close();
    for_each(word_occurences.begin(), word_occurences.end(), &PrintOut);

    return EXIT_SUCCESS;
}

template <typename T>
bool ReadValue(ifstream& in, T* output) {
    T data;
    in >> data;
    if (in.bad()) {
        return false;
    }
    *output = data;
    return true;
}

void PrintOut(const pair<string, int>& p) {
    cout << p.first << " " << p.second << endl;
}
