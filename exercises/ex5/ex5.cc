/*
Arjun Srivastava
arj1@uw.edu
CSE 333
Copyright 2022 Arjun Srivastava
*/

#include <iostream>  // for cout, endl
#include <cstdlib>  // for EXIT_SUCCESS

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

// Print all factors of n
void factorize(int n);

int main(int argc, char** argv) {
    int n;
    cout << "Which positive integer would you like me to factorize? ";

    cin >> n;
    if (n <= 0) {
        cerr << "Please enter a single positive integer\n";
        return EXIT_FAILURE;
    }
    factorize(n);
    return EXIT_SUCCESS;
}

void factorize(int n) {
    for (int i = 1; i < n; i++) {
        if (n % i == 0) cout << i << " ";
    }
    cout << n << endl;
}
