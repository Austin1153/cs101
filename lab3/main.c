#include <stdio.h>

int my_strlen(char* s) {
    int len = 0;
    while(s[len]) len++;
    return len;
}

int rec_strlen(char* s) {
    if(*s++ == 0) return 0; 
    return 1 + rec_strlen(s);
}

char* my_sort(char* s) {
    int len = 0;
	for(int i = 0; *(s + i) != '\0'; i++) len++;
	for(int i = 0; i < len; i++) {
		for(int j = 0; j < len - 1 - i; j++) {
			if(*(s + j) > *(s + j + 1)) {
				char temp = *(s + j);
					*(s + j) = *(s + j + 1);
					*(s + j + 1) = temp;
			}
		}
	}
	return s;
}

int main() {
    char s[] = "IU is a girl!";
    printf("len = %d\n", my_strlen(s));
    printf("len = %d\n", rec_strlen(s));
    printf("sort = %s\n", my_sort(s));
}