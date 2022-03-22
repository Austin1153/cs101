#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Record_in_File "record.bin"
#define Record_out_File "record.txt"

typedef struct lotto_record {
    int lotto_no;
    int lotto_receipt;
    int emp_id;
    char lotto_date[12];
    char lotto_time[10];
} l_record_t;

typedef struct lotto_statistic {
    int lotto_no;
    int lotto_receipt;
    char lotto_date[12];
} stat_t;

int main() {
    FILE *fp;
    fp = fopen(Record_in_File,"rb+");
    l_record_t tmp;
    stat_t stat[10];
    int i = 0;
    while (fread(&tmp,sizeof(l_record_t),1,fp)) {
        if (stat[i].lotto_date == NULL) {
            stat[i].lotto_date = tmp.lotto_date;
        }
        if (stat[i].lotto_date != tmp.lotto_date) {
            i++;
            stat[i].lotto_date = tmp.lotto_date;
        }
        stat[i].lotto_no += 1;
        
    }
}