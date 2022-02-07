/*
Arjun Srivastava
arj1@uw.edu
CSE 333
Copyright 2022 Arjun Srivastava
*/

#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

namespace vector333 {
// A Vector represents a vector in 3-space.
class Vector {
 public:
    Vector();
    Vector(const float x, const float y, const float z);
    Vector(const Vector& copyme);
    ~Vector() { delete[] xyz_; }

    // Assignment operator
    Vector& operator=(const Vector& rhs);

    // Updating assignment
    Vector& operator+=(const Vector& rhs);
    Vector& operator-=(const Vector& rhs);

    // Arithmetic operators
    Vector operator+(const Vector& rhs) const;
    Vector operator-(const Vector& rhs) const;
    friend std::ostream& operator<<(std::ostream& s, const Vector& v);

    // Multiplication
    friend Vector operator*(const Vector& v, const float k);
    friend Vector operator*(const float k, const Vector& v);
    friend float operator*(const Vector& v1, const Vector& v2);

 private:
    float* xyz_;
};
}  // namespace vector333


#endif  // VECTOR_H_
