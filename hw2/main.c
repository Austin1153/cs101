#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int n=6;
void arr_swap(int *arr){
    int tmp;
    for(int i=0;i<n;i++) {
       for(int j=0;j<i;j++) {
           if(arr[j]>arr[i]) {
               tmp=arr[j];
               arr[j]=arr[i];
               arr[i]=tmp;
           }
       }
    }
}    
void print_value(FILE*fp) {
    int i,j,a[6],b[6];
    for(i=1;i<=n;i++) {
        do {
            a[i-1]=(rand() % 69)+1;
            for(j=1;j<i;j++) {
                if(a[i-1]==a[j-1]) {
                    break;
                }
            }
        }while(j!=i);
        b[i-1] = a[i-1];
    }
    arr_swap(b);
    for(int k=0;k<n;k++) {
        fprintf(fp,"%0*d ",2,b[k]);
    }
    fprintf(fp,"%0*d",2,(rand()%10)+1);
    fprintf(fp,"\n");
}
void print_slash(int i, int l, FILE*fp) {
    for(int j=1;j<=i;j++) {
        fprintf(fp, "[%d]: ",l+j);
        for(int k=0;k<n;k++) {
            fprintf(fp, "-- ");
        }
        fprintf(fp, "--");
        fprintf(fp, "\n");
    }
}
typedef struct record {
    int lotto_no;
    int lotto_receipt;
    int lotto_emp_id;
    char lotto_date[128];
    char lotto_time[128];
}typerecord;

typedef struct emp {
    int emp_id;
    char emp_name[32];
    int emp_salary;
}typeemp;

int main() {
    FILE*fp;
    FILE*bin;
    
    int i;
    int k;
    int t_line=5;
    int lotto[10];
    time_t curtime;
    time(&curtime);
    srand(time(NULL));
    int counter[] ={1};
    if((bin=fopen("count.bin","r"))!=NULL) {
        fread(counter,sizeof(int),1,bin);
        counter[0]+=1;
    }
        bin=fopen("count.bin","wb+");
        fwrite(counter,sizeof(int),1,bin);
        fclose(bin);   
    printf("歡迎光臨長庚樂透蓋買機台\n");
    printf("請輸入操作人員ID: ");
    FILE*op;
    int id[] ={0};
    scanf("%d",&id[0]);
    if(id[0]>5) {
        printf("請重新輸入\n");
        exit(1);
    }
    if((op=fopen("id_name.bin","r"))!=NULL) {
        fread(id,sizeof(int),1,op);
    }
        op=fopen("id_name.bin","wb+");
        fwrite(id,sizeof(int),1,op);
        fclose(op);
    FILE*rec;  
    char szbuff[32];
    time_t now = time(0);
    rec=fopen("records.bin","ab+");
    typerecord lotto_record_t;
    strftime(lotto_record_t.lotto_date,100, " %Y%m%d\n",localtime(&now));
    strftime(lotto_record_t.lotto_time,100, " %H:%M:%S\n",localtime(&now));
    lotto_record_t.lotto_no = counter[0];
    lotto_record_t.lotto_receipt = i*50*1.1;
    lotto_record_t.lotto_emp_id = id[0];
    fwrite (&lotto_record_t,sizeof(lotto_record_t),1,rec);
    fclose(rec);
    
    FILE*em;
    em=fopen("operator id.bin","ab+");
    typeemp emp_record_t;
    if(id[0]==0) {
    printf("請輸入要新增操作人員ID: ");
    scanf("%d",&emp_record_t.emp_id);
    if(emp_record_t.emp_id>=100) {
        printf("Please try again!");
        exit(1);
    }else{
        printf("請輸入要新增操作人員NAME: ");
        scanf("%s",emp_record_t.emp_name);
        printf("請輸入要新增操作人員SALARY: ");
        scanf("%d",&emp_record_t.emp_salary);
        fwrite(&emp_record_t,sizeof(emp_record_t),1,em);
        fclose(em);
    }
    
    }else{
         printf("請問您要買幾組樂透彩: ");
    scanf("%d",&i);
    if(1<=i&&i<=5) {
        printf("已為您購買的%d組樂透組合輸出至 lotto.txt",i);
    }else {
        printf("請重新輸入");
    }
    int n =  snprintf(NULL, 0, "lotto[%05d].txt",counter[0]);
    char s1[n+1];
    snprintf(s1, sizeof(s1), "lotto[%05d].txt",counter[0]);
    fp=fopen(s1,"w+");
    fprintf(fp,"======== lotto649 ========\n");
    fprintf(fp,"=======+ No.%05d +=======\n",counter[0]);
    fprintf(fp,"%s",ctime(&curtime));
    for(int j=1;j<=i && j<=5;j++) {
        fprintf(fp,"[%d]: ",j);
        print_value(fp);
    }
    if(t_line>1) print_slash(t_line-i,i,fp);
    fprintf(fp,"========* Op.%05d *========\n",id[0]);
    fprintf(fp,"======== @csieCGU ========");
    fclose(fp);
    }
}