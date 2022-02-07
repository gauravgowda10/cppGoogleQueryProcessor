/*
Arjun Srivastava
arj1@uw.edu
CSE 333
Copyright 2022 Arjun Srivastava
*/

#include <iostream>  // for cout, endl
#include <cstdlib>  // for EXIT_SUCCESS
#include "Vector.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

using vector333::Vector;

int main() {
    Vector v1(1, 2, 5);
    Vector v2;
    Vector v3(v1);

    Vector v4 = v1 * 2;
    Vector v5 = 2 * v1;

    float dot = v1 * v3;
    if (!dot) {
        cerr << "Failed to return dot product" << endl;
        return EXIT_FAILURE;
    }

    // Due to not having getter methods, client should verify outputs in stdout

    cout << "Default constructor should return Vector (0, 0, 0):\n"
        << v2 << endl;

    cout << "Constructor should return Vector (1, 2, 5):\n" << v1 << endl;

    cout << "Copy constructor should return Vector (1, 2, 5):\n"
        << v3 << endl;
    cout << "2 * v matches v * 2:\n" << v4 << "\n" << v5 << endl;

    cout << "dot product v1 * v3 returns 30:\n" << dot << endl;

    v1 += v3;
    cout << "Updating + assignment should return Vector (2, 4, 10):\n"
        << v1 << endl;

    v1 -= v3;
    cout << "Updating - assignment should return Vector (1, 2, 5):\n"
        << v1 << endl;

    Vector v6 = v1 + v1 + v1;
    cout << "Addition operator should return Vector (3, 6, 15):\n"
        << v6 << endl;

    Vector v7 = v6 - v6;
    cout << "Subtraction operator should return Vector (0, 0, 0):\n"
        << v7 << endl;

    return EXIT_SUCCESS;
}
