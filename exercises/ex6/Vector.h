/*
Arjun Srivastava
arj1@uw.edu
CSE 333
Copyright 2022 Arjun Srivastava
*/

#ifndef EXERCISES_EX6_VECTOR_H_
#define EXERCISES_EX6_VECTOR_H_

class Vector {
 public:
    Vector() : x_(0), y_(0), z_(0) { }  // Default constructor
    Vector(const float x, const float y, const float z) :
        x_(x), y_(y), z_(z) { }
    Vector(const Vector& copyme) :
        x_(copyme.x_), y_(copyme.y_), z_(copyme.z_) { }
    ~Vector() {}
    Vector& operator= (const Vector& rhs);
    Vector operator+ (const Vector& rhs);
    Vector operator+= (const Vector& rhs);
    Vector operator-= (const Vector& rhs);
    Vector operator- (const Vector& rhs);
    float operator*(const Vector& rhs);
    float get_x() const { return x_; }
    float get_y() const { return y_; }
    float get_z() const { return z_; }

 private:
    float x_, y_, z_;
};
#endif  // EXERCISES_EX6_VECTOR_H_
