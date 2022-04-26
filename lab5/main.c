#include <stdio.h>
#include <stdlib.h>

typedef struct array_list {
    int n;
    int* (*Get_int_arr_fp)(int);
    void (*SET_value_fp)(int*, int);
    void (*Print_arr_fp)(int*, int);
} array_list_t;

int* get_int_array(int n) {
    int* ip = (int*)calloc(n, sizeof(int));
    return ip;
}

void set_value(int* p, int v) {
    *p = v;
}

void print_array(int* p, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        if (i == n-1) {
            printf("%d]\n", *(p+i));
        } else {
            printf("%d, ", *(p+i));
        }
    }
    free(p);
}

char* func(char a[], char b[]) {
    return a+b;
}

char* add_str_func(char a[], char b[], char* (*func_ptr)(char, char)) {
    return func_ptr(a, b);
}

int main() {
    printf("No.1-----------------------------------\n");
    int n = 10;
    int* ip = get_int_array(n);

    for (int i = 0; i < n; i++) {        
        set_value(ip+i, i+1);
    }

    print_array(ip,n);
    // func 2
    printf("No.2-----------------------------------\n");
    array_list_t p;
    p.Get_int_arr_fp = get_int_array;
    p.SET_value_fp = set_value;
    p.Print_arr_fp = print_array;
    p.n = 20;

    int* ptr = p.Get_int_arr_fp(p.n);

    for (int i = 0; i < p.n; i++) {        
        p.SET_value_fp(ptr+i, i+1);
    }

    p.Print_arr_fp(ptr,p.n);
    // func 3
    printf("No.3-----------------------------------\n");
    char a[] = "IU!IU!";
    char b[] = "@CGU";
    printf("add_str_func = %s\n", add_str_func(a, b, func));
    return 0;
}