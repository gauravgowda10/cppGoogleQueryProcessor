/*
Arjun Srivastava
arj1@uw.edu
CSE 333
Copyright 2022 Arjun Srivastava
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> 

/*
Takes in an array of bytes and a byte length and prints out the length, 
the address passed in, and the bytes of memory as exactly two digits each in lowercase hexadecimal
*/
void DumpBytes(void* pData, int32_t byteLen);

/*
Sorts and copies contents of arr1 into arr2 using insertion sort
*/
void CopyAndSort(uint8_t arr1[], uint8_t arr2[], int arrayLen);

int main(int argc, char* argv[]) {
  int32_t int_val = 1;
  float   float_val = 1.0f;
  uint8_t arr_unsorted[] = {3, 2, 0, 8, 17, 6, 10, 7, 8, 1, 12};
  uint8_t arr_sorted[]   = {0, 0, 0, 0,  0, 0,  0, 0, 0, 0,  0};

  DumpBytes(&int_val, sizeof(int_val));
  DumpBytes(&float_val, sizeof(float_val));
  DumpBytes(arr_unsorted, sizeof(arr_unsorted));
  CopyAndSort(arr_unsorted, arr_sorted, sizeof(arr_unsorted));
  DumpBytes(arr_sorted, sizeof(arr_sorted));

  return EXIT_SUCCESS;
}

void DumpBytes(void* pData, int32_t byteLen) {
    int i;
    uint8_t* byteData = (uint8_t*) pData;

    printf("The %d bytes starting at %p are:", byteLen, byteData);
    for (i = 0; i < byteLen; i++) {
        uint8_t byte = byteData[i];
        printf(" %02" PRIx8, byte);
    }
    printf("\n");
}

void CopyAndSort(uint8_t arr1[], uint8_t arr2[], int arrayLen) {
    DumpBytes(arr1, sizeof(arr1));
    int i;
    for (i = 0; i < arrayLen; i++) {
        // Sorting not implemented yet
        arr2[i] = arr1[i];
    }
}
