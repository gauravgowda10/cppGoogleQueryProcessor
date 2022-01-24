/*
Arjun Srivastava
arj1@uw.edu
CSE 333
Copyright 2022 Arjun Srivastava
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Point3d.h"

int main(int argc, char* argv[]) {
    // Test Point3d_Allocate()
    Point3d* point = Point3d_Allocate(5, 6, 7);
    if (point) {
        assert(point->x == 5);
        assert(point->y == 6);
        assert(point->z == 7);    
    } else {
        fprintf(stderr, "Allocation failed\n");
        return EXIT_FAILURE;
    }

    // Test Point3d_Scale()
    Point3d* bad_point = NULL;
    Point3d_Scale(bad_point, 10);   // Should print error
    Point3d_Scale(point, 2);
    assert(point->x == 10);
    assert(point->y == 12);
    assert(point->z == 14);

    // Test Point3d_GetOrigin
    Point3d origin = Point3d_GetOrigin();
    assert(origin.x == 0);
    assert(origin.y == 0);
    assert(origin.z == 0);

    free(point);
    printf("Success!\n");
    return EXIT_SUCCESS;
}
