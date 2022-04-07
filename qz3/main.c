#include <stdio.h>

void rec_dec(char* s) {
    if (*s == '\0') {
        printf("\n");
    } else {
        printf("%c,", *s++);
        rec_dec(s);
    }
}

int hanoi_tower_f(int num, char from, char mid, char dest) {
    FILE *fp;
    if (num == 1) {
        fp = fopen("hanoi.txt", "a+");
        fprintf(fp, "Move disk %d from %c to %c\n", num, from, dest);
        fclose(fp);
    } else {
    hanoi_tower_f(num - 1, from, dest, mid);
    fp = fopen("hanoi.txt", "a+");
    fprintf(fp, "Move disk %d from %c to %c\n", num, from, dest);
    fclose(fp);
    hanoi_tower_f(num - 1, mid, from, dest);
    }
}

void hanoi_tower(int num) {
    FILE *fp;
    if (fopen("hanoi.txt","r+") == NULL) {
        fp = fopen("hanoi.txt", "w");
        fclose(fp);
    }
    hanoi_tower_f(num, 'A', 'B', 'C');
}

int multiplication(int i, int j) {
    if (i == 9 && j == 10) {
        printf("\n");
        return 0;
    }
    if (j == 10) {
        j = 1;
        i++;
        printf("\n");
    }
    printf("%d*%d=%2d ", i, j, i*j);
    multiplication(i, ++j);
}

int main() {
    char s[] = "1234567890";
    rec_dec(s);
    printf("func#1---------------------------\n");
    hanoi_tower(16);
    printf("func#2---------------------------\n");
    multiplication(1, 1);
    printf("func#3---------------------------\n");
    return 0;
}