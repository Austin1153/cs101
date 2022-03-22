#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct record {
  int lotto_no;
  int lotto_receipt;
  int lotto_emp_id;
  char lotto_date[128];
  char lotto_time[128];
}typerecord;

int main() {
  FILE* fp, * rfp = fopen("records.bin", "r");
  char now[9], doi[9] = "";
  int slots = 0, receipts = 0, tdoi = 1, tslots = 0, treceipts = 0;
  typerecord record[1];
  time_t date = time(NULL);
  srand((unsigned)time(NULL));
  if (rfp == NULL) {
    printf("Empty record\nReport will not be generated\n");
    return 0;
  } else fp = fopen("report.txt", "w+");
  fprintf(fp, "========= lotto649 Report =========\n");
  fprintf(fp, "- Date ------ Num. ------ Receipt -\n");
  for (int i = 0; fread(record, sizeof(typerecord), sizeof(record) / sizeof(record[0]), rfp); i++) {
    if (doi[0] == '\0' || strcmp(doi, record[0].lotto_date) == 0) {
      sprintf(doi, "%s", record[0].lotto_date);
      slots++;
      receipts += record[0].lotto_receipt;
      tslots++;
      treceipts += record[0].lotto_receipt;
    } else if (strcmp(doi, record[0].lotto_date) != 0) {
      fprintf(fp, "%s\t%d/%d\t\t%d\n", doi, slots, receipts / 55, receipts);
      sprintf(doi, "%s", record[0].lotto_date);
      slots = 1;
      receipts = record[0].lotto_receipt;
      tdoi++;
      tslots++;
      treceipts += record[0].lotto_receipt;
    };
  };
  fprintf(fp, "%s\t%d/%d\t\t%d\n", doi, slots, receipts / 55, receipts);
  fclose(rfp);
  fprintf(fp, "-----------------------------------\n");
  fprintf(fp, "       %d\t%d/%d\t\t%d\n", tdoi, tslots, treceipts / 55, treceipts);
  strftime(now, 100, "%Y%m%d", localtime(&date));
  fprintf(fp, "======== %s Printed =========\n", now);
  fclose(fp);
  return 0;
}
