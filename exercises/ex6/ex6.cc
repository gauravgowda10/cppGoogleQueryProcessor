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

void Increment(Vector v);

bool VerifyAddress(const Vector& v, void* ptr);

int main() {
    Vector test1;
    cout << "Testing default constructor" << endl;
    if (test1.get_x() == 0 && test1.get_y() == 0 && test1.get_z() == 0) {
        cout <<
        "Passed: default constructor correctly initialized Vector"
        << endl;
    } else {
        cout <<
        "Failed: default constructor incorrectly initialized Vector"
        << endl;
        return EXIT_FAILURE;
    }

    Vector test2(1, 2, 3);
    cout << "Testing constructor" << endl;
    if (test2.get_x() == 1 && test2.get_y() == 2 && test2.get_z() == 3) {
        cout << "Passed: constructor correctly initialized Vector" << endl;
    } else {
        cout << "Failed: constructor incorrectly initialized Vector" << endl;
        return EXIT_FAILURE;
    }

    Vector test3(test2);
    cout << "Testing copy constructor" << endl;
    if (test3.get_x() == 1 && test3.get_y() == 2 && test3.get_z() == 3) {
        cout << "Passed: copy constructor correctly initialized Vector" << endl;
    } else {
        cout <<
        "Failed: copy constructor incorrectly initialized Vector"
        << endl;
        return EXIT_FAILURE;
    }

    cout << "Testing assignment operator" << endl;
    Vector test4;
    test4 = test3;
    if (test4.get_x() == 1 && test4.get_y() == 2 && test4.get_z() == 3) {
        cout << "Passed: assignment operator correctly updated values" << endl;
    } else {
        cout <<
        "Failed: assignment operator incorrectly updated values"
        << endl;
        return EXIT_FAILURE;
    }

    cout << "Testing addition operator" << endl;
    Vector test5;
    test5 = test3 + test4;
    if (test5.get_x() == 2 && test5.get_y() == 4 && test5.get_z() == 6) {
        cout << "Passed: addition operator correctly updated values" << endl;
    } else {
        cout << "Failed: addition operator incorrectly updated values" << endl;
        return EXIT_FAILURE;
    }

    cout << "Testing addition update operator" << endl;
    Vector adder(1, 1, 1);
    test1 += adder;
    if (test1.get_x() == 1 && test1.get_y() == 1 && test1.get_z() == 1) {
        cout <<
        "Passed: addition update operator correctly updated values"
        << endl;
    } else {
        cout <<
        "Failed: addition update operator incorrectly updated values"
        << endl;
        return EXIT_FAILURE;
    }

    cout << "Testing subtraction update operator" << endl;
    test1 -= adder;
    if (test1.get_x() == 0 && test1.get_y() == 0 && test1.get_z() == 0) {
        cout <<
        "Passed: subtraction update operator correctly updated values"
        << endl;
    } else {
        cout <<
        "Failed: subtraction update operator incorrectly updated values"
        << endl;
        return EXIT_FAILURE;
    }

    cout << "Testing subtraction operator" << endl;
    Vector test6;
    test6 = test3 - test4;
    if (test6.get_x() == 0 && test6.get_y() == 0 && test6.get_z() == 0) {
        cout <<
        "Passed: subtraction operator correctly updated values"
        << endl;
    } else {
        cout <<
        "Failed: subtraction operator incorrectly updated values"
        << endl;
        return EXIT_FAILURE;
    }

    cout << "Testing multiplication operator" << endl;
    float dot_product;
    dot_product = test5 * test3;
    if (dot_product == (test5.get_x()*test3.get_x() +
            test5.get_y()*test3.get_y() + test5.get_z()*test3.get_z())) {
        cout << "Passed: multiplication operator returns dot product" << endl;
    } else {
        cout << "Failed: multiplication operator returns dot product" << endl;
        return EXIT_FAILURE;
    }

    Vector test7;
    cout << "Testing increment" << endl;
    Increment(test7);
    if (test7.get_x() == 1) {
        cout << "Vector: pass-by-reference" << endl;
    } else {
        cout << "Vector: pass-by-value" << endl;
    }

    cout << "Testing addresses" << endl;
    Vector* test7ptr = &test7;
    Vector& test7ref = test7;
    bool sameVector = VerifyAddress(test7ref, test7ptr);
    if (sameVector) {
        cout << "Ref: same address" << endl;
    } else {
        cout << "Ref: different address" << endl;
    }
}

void Increment(Vector v) {
    Vector temp(1, 1, 1);
    v += temp;
}

bool VerifyAddress(const Vector& v, void* ptr) {
    Vector* pointed = reinterpret_cast<Vector*>(ptr);
    return &v == &*pointed;
}
