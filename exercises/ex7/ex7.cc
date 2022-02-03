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
    Vector v2();
    Vector v3(v1);

    Vector _v2_ = v1 * 2;
    Vector _2v_ = 2 * v1;
    cout << "2 * v matches v * 2:\n" << _v2_ << "\n" << _2v_ << endl;


    return EXIT_SUCCESS;
}
