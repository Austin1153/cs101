#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Counter_File "count.bin"
#define User_log_File "userlog.bin"
#define Record_file "record.bin"

typedef struct lotto_record {
    int lotto_no;
    int lotto_receipt;
    int emp_id;
    char lotto_date[12];
    char lotto_time[10];
} lotto_record_t;

int check_input(int input_for_check) {
    if (input_for_check > 5 || input_for_check < 1) {
        printf("error! input must be an integer in range 1~5\nplease restart program");
        return 1;
    } else {
        return 0;
    }
}

void userf(int id) {
    int n;
    FILE *fp;
    if ((fp = fopen(User_log_File,"rb+")) == NULL) {
        n = 0;
        fp = fopen(User_log_File,"wb");
        fclose(fp);
    }
    fp = fopen(User_log_File,"ab+");
    fwrite(&id,sizeof(int),1,fp);
    fclose(fp);
}

void store_recordf(lotto_record_t record) {
    FILE *fp;
    if ((fp = fopen(Record_file,"rb+")) == NULL) {
        fp = fopen(Record_file,"wb");
        fclose(fp);
    }
    fp = fopen(Record_file,"ab+");
    fwrite(&record,sizeof(record),1,fp);
    fclose(fp);
}

void record_lotto_f(int lotto_no,int n,int emp_id) {
    lotto_record_t record;
    time_t now = time(0);
    record.lotto_no = lotto_no;
    record.lotto_receipt = n*50*1.1;
    record.emp_id = emp_id;
    strftime(record.lotto_date,12,"%Y/%m/%d",localtime(&now));
    strftime(record.lotto_time,10,"%H:%M:%S",localtime(&now));
    store_recordf(record);
}

int countf() {
    int n;
    FILE *fp;
    if ((fp = fopen(Counter_File,"rb+")) == NULL) {
        n = 0;
        fp = fopen(Counter_File,"wb");
        fwrite(&n,sizeof(int),1,fp);
        fclose(fp);
    }
    fp = fopen(Counter_File,"rb+");
    fread(&n,sizeof(int),1,fp);
    fclose(fp);

    n = n + 1;
    fp = fopen(Counter_File,"wb+");
    fwrite(&n,sizeof(int),1,fp);
    return n;
}

void sort_arr(int lotto[]) {
    int tmp = 70, tmpn = 0;
    for (int i = 0; i <= 5; i++) {
        tmp = 70, tmpn = 7;
        for (int j = i; j <= 5; j++) {
            if (tmp > lotto[j]) {
                tmp = lotto[j];
                tmpn = j;
            }
        }
        lotto[tmpn] = lotto[i];
        lotto[i] = tmp;
    }
}

void lottof(int lotto[]) {
    int flag = 0;
    //generate special number
    lotto[6] = (rand()%10)+1;
    //generate lotto number
    for (int i = 0, tmp = 0; i < 6;) {
        tmp = (rand() % 69)+1;
        if (tmp == lotto[6]) continue; //check if repeat with spec.num
        for (int j = 0; j < i; j++) { //check if repeat 
            if (lotto[j] == tmp) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            flag = 0;
            continue;
        } else {
            lotto[i++] = tmp;
        }
    }
}

int main() {
    int n,user_id,op_id;
    printf("enter operator id to logged in\n");
    scanf("%d",&op_id);
    printf("welcome to lotto program, \nplease log in first");
    printf("\nuser(1~5) : ");
    scanf("%d",&user_id);
    if(check_input(user_id)) exit(0);
    printf("enter the amount of lotto to buy.\namount : ");
    scanf("%d",&n);
    if(check_input(n)) exit(0);
    //deal with time and random
    time_t currtime = time(&currtime);
    char str_curtime[25];
    snprintf(str_curtime,sizeof(str_curtime),"%s",ctime(&currtime));
    srand(time(NULL));
    //record bin
    int count = countf();
    record_lotto_f(count,n,op_id);
    //generating lotto numbers
    char lotto_name[17];
    snprintf(lotto_name,sizeof(lotto_name),"lotto[%05d].txt",count);
    userf(user_id);
    int lotto[7];
    //file management 
    FILE *fp;
    fp = fopen(lotto_name,"w+");
    fprintf(fp,"========= lotto048 =========\n");
    fprintf(fp,"========+ No.%05d +========\n",count);
    fprintf(fp,"= %s =\n",str_curtime);
    for (int i = 1; i <= 5; i++) {
        fprintf(fp,"[%d]:",i);
        if (i <= n) {
            lottof(lotto);
            sort_arr(lotto);
            for (int i = 0; i <= 6; i++) {
                fprintf(fp," %0*d",2,lotto[i]);
            }
            fprintf(fp,"\n");
        } else {
            for (int i = 0; i <= 6; i++) {
                fprintf(fp," --");
            }
            fprintf(fp,"\n");
        }
    }
    fprintf(fp,"========* Op.%05d *========\n",user_id);
    fprintf(fp,"========= csie@CGU =========");
    fclose(fp);
    return 0;
}