/*
Arjun Srivastava
arj1@uw.edu
CSE 333
Copyright 2022 Arjun Srivastava
*/

#include <iostream>
#include "Vector.h"

namespace vector333 {

Vector::Vector() {
    xyz_ = new float[3];
    xyz_[0] = 0.0;
    xyz_[1] = 0.0;
    xyz_[2] = 0.0;
}

Vector::Vector(const float x, const float y, const float z) {
    xyz_ = new float[3];
    xyz_[0] = x;
    xyz_[1] = y;
    xyz_[2] = z;
}

Vector::Vector(const Vector& copyme) {
    xyz_ = new float[3];
    xyz_[0] = copyme.xyz_[0];
    xyz_[1] = copyme.xyz_[1];
    xyz_[2] = copyme.xyz_[2];
}

Vector& Vector::operator=(const Vector& rhs) {
    if (this != &rhs) {
        xyz_[0] = rhs.xyz_[0];
        xyz_[1] = rhs.xyz_[1];
        xyz_[2] = rhs.xyz_[2];
    }
    return *this;
}

Vector Vector::operator+(const Vector& rhs) const {
    Vector newVector(xyz_[0] + rhs.xyz_[0],
                     xyz_[1] + rhs.xyz_[1],
                     xyz_[2] + rhs.xyz_[2]);
    return newVector;
}

Vector Vector::operator-(const Vector& rhs) const {
    Vector newVector(xyz_[0] - rhs.xyz_[0],
                    xyz_[1] - rhs.xyz_[1],
                    xyz_[2] - rhs.xyz_[2]);
    return newVector;
}

Vector& Vector::operator+=(const Vector& rhs) {
    xyz_[0] += rhs.xyz_[0];
    xyz_[1] += rhs.xyz_[1];
    xyz_[2] += rhs.xyz_[2];
    return *this;
}

Vector& Vector::operator-=(const Vector& rhs) {
    xyz_[0] -= rhs.xyz_[0];
    xyz_[1] -= rhs.xyz_[1];
    xyz_[2] -= rhs.xyz_[2];
    return *this;
}

std::ostream& operator<<(std::ostream& s, const Vector& v) {
    s << "(" << v.xyz_[0] << "," << v.xyz_[1] << "," << v.xyz_[2] << ")";
    return s;
}

Vector operator*(const Vector& v, const float k) {
    Vector newVector(v.xyz_[0] * k, v.xyz_[1] * k, v.xyz_[2] * k);
    return newVector;
}

Vector operator*(const float k, const Vector& v) {
    Vector newVector(v.xyz_[0] * k, v.xyz_[1] * k, v.xyz_[2] * k);
    return newVector;
}

float operator*(const Vector& v1, const Vector& v2) {
    return v1.xyz_[0] * v2.xyz_[0]
         + v1.xyz_[1] * v2.xyz_[1]
         + v1.xyz_[2] * v2.xyz_[2];
}

}  // namespace vector333
