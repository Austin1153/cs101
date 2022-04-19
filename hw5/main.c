#include <stdio.h>

typedef struct my_mm {
    int stat_mms[10];
    int rec_mms[10];
} my_mm_t;

int g_mem[10];
my_mm_t mms;

void print_stat_mem(int opt) {
    for (int i = 0; i < 10; i++) printf("%d", mms.stat_mms[i]);
    if (opt == 1) {
    } else {
        printf("\n");
    }
}

int find_size(int n[], int size) {
    int count = 0,i = 0;
    for(; i < 10; i++) {
        if (n[i]) {
            count = 0;
        } else {
            count++;
        }
        if (count == size) break;
    }
    return i - size + 1;
}

int find_maxsize(int n[]) {
    int count = 0, tmp = 0;
    for (int i = 0; i < 10; i++) {
        if (n[i]) {
            if (tmp > count) {
                count = tmp;
                tmp = 0;
            }
        } else {
            tmp++;
        }
    }
    if (tmp > count) count = tmp;
    return count;
}

int new_record_num() {
    int num = 1;
    for(int i = 0; i < 10; i++) {
        if(num == mms.rec_mms[i]) {
            num++;
            i = 0;
        }
    }
    return num;
}

void record(int start_loc, int size) {
    int rec_num = new_record_num();
    for (int i = start_loc; i < start_loc + size; i++) {
        mms.stat_mms[i] = 1;
        mms.rec_mms[i] = rec_num;
    }
}

int* my_calloc(int n, int size) {
    if(size > find_maxsize(mms.stat_mms)) {
        print_stat_mem(1);
        printf(" <- Out of space\n");
        return NULL;
    } else {
        int loc = find_size(mms.stat_mms, size);
        record(loc, size);
        print_stat_mem(0);
        return &g_mem[loc];
    }
}

void my_free(int* p) {
    int loc = p - g_mem;
    int del_rec = mms.rec_mms[loc];
    for(int i = 0; i < 10; i++) {
        if(mms.rec_mms[i] == del_rec) {
            mms.rec_mms[i] = 0;
            mms.stat_mms[i] = 0;
        }
    }
    print_stat_mem(0);
}

int main() {
    int* p1 = my_calloc(1,1);
    int* p2 = my_calloc(1,2);
    int* p3 = my_calloc(1,3);
    int* p4 = my_calloc(1,4);
    my_free(p1);
    my_free(p4);
    int* p5 = my_calloc(1,5);
    int* p6 = my_calloc(1,1);
    return 0;
}