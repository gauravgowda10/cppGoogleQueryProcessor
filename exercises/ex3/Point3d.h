/*
Arjun Srivastava
arj1@uw.edu
CSE 333
Copyright 2022 Arjun Srivastava
*/

#ifndef EXERCISES_EX3_POINT3D_H_
#define EXERCISES_EX3_POINT3D_H_

#include <stdint.h>

typedef struct point {
        int32_t x, y, z;
    } Point3d;

/*
Allocates new Point3d and returns pointer to it
*/
Point3d* Point3d_Allocate(int32_t x, int32_t y, int32_t z);

/*
Scales point's x, y, and z values by the given int
*/
void Point3d_Scale(Point3d* point, int32_t scale);

/*
Constructs a new Point3d with x = y = z = 0 and returns a copy of the struct
*/
Point3d Point3d_GetOrigin();

#endif  // EXERCISES_EX3_POINT3D_H_
