#include <stdio.h>
#include <stdlib.h>

void swap(int* n, int* m) {
    int tmp = *n;
    *n = *m;
    *m = tmp;
}

void swapArray(int source[], int dest[], int size) {
    int tmp;
    for(int i = 0; i < size; i++) {
        tmp = source[i];
        source[i] = dest[i];
        dest[i] = tmp;
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i + 1 < size) {
            printf(", ");
        } else {
            printf("]\n");
        }
    }
}

char* copy_string(char str[]) {
    int size = 0;
    while (str[size]) size++;
    char* ptr = (char*)calloc(1, size);
    for (int i = 0; i < size; i++) {
        *(ptr+i) = str[i];
    }
    return ptr;
}

int main() {
    int n, m;
    n = 1;
    m = 2;
    printf("No.1------------------\n");
    swap(&n,&m);
    printf("after swap, n = %d, m = %d\n", n, m);
    printf("No.2------------------\n");
    int size = 10;
    int source[10] = {0,9,8,7,6,5,4,3,2,1};
    int dest[10] = {10,20,30,40,50,60,70,80,90,100};
    swapArray(source, dest, size);
    printf("after swap array, source array = [");
    printArray(source, size);
    printf("after swap array, dest array = [");
    printArray(dest, size);
    printf("No.3------------------\n");
    char str[] = "IU!IU!IU!IU!";
    char* cp_str = copy_string(str);
    printf("copy string = %s\n", cp_str);
    free(cp_str);
    return 0;
}