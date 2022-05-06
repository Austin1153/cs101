#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Counter_File "count.bin"
#define User_log_File "userlog.bin"

void namef(char name[],int c) {
    for (int i = 8; i >= 5; i--,c /= 10) {
        name[i] = (c%10+'0');
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
    lotto[6] = (rand()%10)+1;
    for (int i = 0, tmp = 0; i < 6; i++) {
        tmp = (rand() % 69)+1;
        if (tmp == lotto[6]) continue;
        for (int j = 0; j < i; j++) {
            if (lotto[j] == tmp) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            flag == 0;
            continue;
        } else {
            lotto[i] = tmp;
        }
    }
}

int main() {
    printf("welcome to lotto program, \nenter the amount of lotto to buy.\n");
    printf("amount : ");
    int n,user_id;
    scanf("%d",&n);
    printf("\nuser(1~5) : ");
    scanf("%d",&user_id);
    
    int count = countf();
    char name[14]="lotto    .txt";
    namef(name,count);
    userf(user_id);
    time_t currtime = time(&currtime);
    srand(time(NULL));
    int lotto[7];
    
    FILE *fp;
    fp = fopen(name,"w+");
    fprintf(fp,"========= lotto048 =========\n");
    fprintf(fp,"========+ No.%05d +========\n",count);
    fprintf(fp," %s",ctime(&currtime));
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
