//
// Created by Yuri Grigorian on 04/01/2021.
//

#include <stdlib.h>
#include "isort.h"
#include "stdio.h"

void print_arr(int *arr, int len) {
    for (int i = 0; i < len - 1; i++)
        printf("%d,", arr[i]);
    printf("%d", arr[len - 1]);
}

/// Shift i elemrnts to the right. Assumes there is enough space.
/// \param arr Integer array pointer.
/// \param i Number of elements to shift.
void shift_element(int *arr, int i) {
    for (i = i - 1; i >= 0; --i) {
        int *currentPos = (arr + i);
        *(currentPos + 1) = *currentPos;
    }
}
/// Sort the array using insertion sort.
/// \param arr Pointer to integer array.
/// \param len Array length.
void insertion_sort(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        int *currentItem = arr + i;
        int *newPos = NULL;

        // Traverse array back to find the new position for the element
        for (int j = 1; j <= i; ++j) {
            int *beforeItem = currentItem - j;
            if (*beforeItem > *currentItem) {
                newPos = beforeItem;
            }
        }

        if (newPos != NULL) {
            int newValue = *currentItem;
            int shiftItemsCount = (int) (currentItem - newPos); // Calc number by substracting addresses
            shift_element(newPos, shiftItemsCount);
            *newPos = newValue;
        }
    }
}

int main() {
    int myArr[ARR_SIZE];
    int readCount = 0;

    while (readCount < ARR_SIZE) {
        int lastRead = scanf("%d", &myArr[readCount]);
        if (lastRead == 0 || lastRead == EOF) {
            break;
        }
        readCount++;
    }

    if (readCount != ARR_SIZE) {
        printf("Wrong input given... Exiting.");
        exit(1);
    }

    insertion_sort(myArr, ARR_SIZE);
    print_arr(myArr, ARR_SIZE);
}

