/*
Arjun Srivastava
arj1@uw.edu
CSE 333
Copyright 2022 Arjun Srivastava
*/

#include "Vector.h"

Vector& Vector::operator=(const Vector& rhs) {
    if (this != &rhs) {
        x_ = rhs.x_;
        y_ = rhs.y_;
        z_ = rhs.z_;
    }
    return *this;
}

Vector Vector::operator+(const Vector& rhs) {
    Vector newVector(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_);
    return newVector;
}

Vector Vector::operator+=(const Vector& rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
    return *this;
}

Vector Vector::operator-=(const Vector& rhs) {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
    return *this;
}

Vector Vector::operator-(const Vector& rhs) {
    Vector newVector(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_);
    return newVector;
}

float Vector::operator*(const Vector& rhs) {
    return x_*rhs.x_ + y_*rhs.y_ + z_*rhs.z_;
}
