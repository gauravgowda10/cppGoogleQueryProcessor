/*
Arjun Srivastava
arj1@uw.edu
CSE 333
Copyright 2022 Arjun Srivastava
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "Point3d.h"


Point3d* Point3d_Allocate(int32_t x, int32_t y, int32_t z) {
    Point3d* point = (Point3d*) malloc(sizeof(Point3d));
    point->x = x;
    point->y = y;
    point->z = z;
    return point;
}

void Point3d_Scale(Point3d* point, int32_t scale) {
    // Make sure pointer is valid
    if (point != NULL) {
        point->x *= scale;
        point->y *= scale;
        point->z *= scale;
    } else {
        fprintf(stderr, "Cannot scale null pointer\n");
    }
}

Point3d Point3d_GetOrigin() {
    Point3d point = {
        0, 0, 0
    };
    return point;
}
