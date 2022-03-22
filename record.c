#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void count_sumf(int sum[], int no_sum, int receipt_sum) {
    sum[0] += 1;
    sum[1] += no_sum;
    sum[2] += receipt_sum;
}

int extract_recordf(stat_t stat[],int sum[]) {
    FILE *recordbin;
    recordbin = fopen(Record_in_File,"rb+");
    l_record_t tmp;
    int i = 0;
    while (fread(&tmp,sizeof(l_record_t),1,recordbin)) {
        /*if (stat[i].lotto_date == NULL) {
            stat[i].lotto_date = tmp.lotto_date;
        }*/
        if (strcmp(stat[i].lotto_date, tmp.lotto_date) != 0) {
            if (i == 0) {
                for (int i = 0; i < 3; i++) sum[i] = 0;
            } else {
                count_sumf(sum, stat[i].lotto_no, stat[i].lotto_receipt);
            }
            i++;
            snprintf(stat[i].lotto_date,12,"%s",tmp.lotto_date);
            stat[i].lotto_no = 0;
            stat[i].lotto_receipt = tmp.lotto_receipt;
        }
        stat[i].lotto_no += 1;
        stat[i].lotto_receipt += tmp.lotto_receipt;   
    }
    count_sumf(sum, stat[i].lotto_no, stat[i].lotto_receipt);
    fclose(recordbin);
    return i;
}

void get_time_strf(char date[]){
	time_t now = time(0);
	strftime(date, 10, "%Y%m%d", localtime(&now));
}

int main() {
    stat_t stat[10];
    int sum[3];
    char date[10];
    get_time_strf(date);
    int count_records = extract_recordf(stat, sum);

    FILE *recordp;
    recordp = fopen(Record_out_File,"w+"); 
    fprintf(recordp,"========= lotto048 Report =========\n");
    fprintf(recordp,"- Date ------- Num. ------ Receipt -\n");
    for (int i = 1; i <= count_records; i++) {
        fprintf(recordp,"%s     %d/%2d \t\t %d\n",stat[i].lotto_date,stat[i].lotto_no,stat[i].lotto_receipt/55,stat[i].lotto_receipt);
    }
    fprintf(recordp,"-----------------------------------\n");
	fprintf(recordp,"\t\t%d \t  %d/%d \t \t %d\n", sum[0],sum[1],sum[2]/55,sum[2]);
	fprintf(recordp,"======== %s Printed =========", date);
    fclose(recordp);
}