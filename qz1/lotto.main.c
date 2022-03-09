#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void namef(char name[],int c) {
    for (int i = 8; i >= 5; i--,c /= 10) {
        name[i] = (c%10+'0');
    }
}

int countf() {
    int n;
    FILE *fp;
    if ((fp = fopen("count.bin","rb+")) == NULL) {
        n = 0;
        fp = fopen("count.bin","wb");
        fwrite(&n,sizeof(int),1,fp);
        fclose(fp);
    }
    fp = fopen("count.bin","rb+");
    fread(&n,sizeof(int),1,fp);
    fclose(fp);

    n = n + 1;
    fp = fopen("count.bin","wb+");
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
    int n;
    scanf("%d",&n);
    
    int count = countf();
    char name[10]="lotto";
    namef(name,count);
    time_t currtime = time(&currtime);
    srand(time(NULL));
    int lotto[7];
    
    FILE *fp;
    fp = fopen(name,"w+");
    fprintf(fp,"======== lotto048 ========\n");
    fprintf(fp,"========= %0*d =========\n",6,count);
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
                fprintf(fp," ==");
            }
            fprintf(fp,"\n");
        }
    }
    fprintf(fp,"=========================");
    fclose(fp);
    return 0;
}
