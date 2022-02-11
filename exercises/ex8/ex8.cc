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

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ifstream;
using std::string;
using std::map;

// ADD HELPERs

// Reads the current value from the stream into output
template <typename T>
bool ReadValue(ifstream& in, T* output);

// Accepts a sorted map and prints the outputs
template <typename T, int N>
void PrintWordCounts(map<T, N>& wordOccurrences);

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Please input one .txt file argument" << endl;
        exit(EXIT_FAILURE);
    }
    string filename = argv[1];
    ifstream in;
    in.open(filename);

    if (!in.is_open()) {
        cerr << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }

    // Check other errors when opening file (good, bad, eof)

    string data;
    while (in >> data) {
        bool read = ReadValue(in, &data);
        if (!read) {
            cerr << "Error reading from file" << endl;
            exit(EXIT_FAILURE);
        }
        
    }
    in.close();
    
    return EXIT_SUCCESS;
}

template <typename T>
bool ReadValue(ifstream& in, T* output) {
    return true;
}

void PrintWordCounts(map<T, N>& wordOccurrences) {

}
