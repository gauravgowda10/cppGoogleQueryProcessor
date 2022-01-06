/*
Arjun Srivastava
arj1@uw.edu
CSE 333
Copyright 2022 Arjun Srivastava
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estimates the value of pi using Nilakantha infinite series
double estimate(int n);

// Returns nth term of pi infinite series
double nthTerm(int n);

int main(int argc, char* argv[]) {
    if (argc > 2) {
        printf("Please only input one argument.\n");
        return EXIT_FAILURE;
    }
    int n;
    // Only run if there are arguments
    for (char** arg = argv + 1; *arg; ++arg) {
        int num;
        // Extract integer from argument (ignore trailing alphanumeric chars)
        sscanf(*arg, "%d", &num);
        // If we reach a positive integer value, return estimate
        if (num > 0) {
            n = num;
            double result = estimate(n);
            printf("Our estimate of Pi is %.20f\n", result);
            return EXIT_SUCCESS;
        }
    }
    printf("Please provide a valid input (positive integer) \n");
    return EXIT_FAILURE;    // If there are no valid inputs
}

double estimate(int n) {
    double result = 3;
    int i;
    for (i = 1; i <= n; i++) {
        result += nthTerm(i);
    }
    return result;
}

double nthTerm(int n) {
    double multiplier;
    if (n % 2 == 1) {
        multiplier = 1;
    } else {
        multiplier = -1;
    }
    return multiplier * (4.0 / (2.0*n * (2.0*n + 1.0) * (2.0*n + 2.0)));
}
