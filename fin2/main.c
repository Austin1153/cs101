#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList {
    char data;
    struct LinkedList* tmp;
} LinkedList;

LinkedList* allocNode(char val) {
    LinkedList* last = (LinkedList*)calloc(1,sizeof(LinkedList));
    last->data = val;
    return last;
}

LinkedList* appendList(LinkedList* head, char val) {
    LinkedList* tmp = head;
    if (head == NULL) {
        head = allocNode(val);
        return head;
    }
    while (tmp->tmp != NULL) {
        tmp = tmp->tmp;
    }
    tmp->tmp = allocNode(val);
    return head;
}

void showList(LinkedList* head) {
    while (head->tmp) {
        printf("[%c]->", head->data);
        head = head->tmp;
    }
    printf("[%c]->", head->data);
    printf("null\n");
}

LinkedList* reverseList(LinkedList* head) {
    LinkedList* new = NULL;
    LinkedList* now = head;
    LinkedList* tmp = NULL;
    while (now != NULL) {
        tmp = now->tmp;
        now->tmp = new;
        new = now;
        now = tmp;
    }
    return new;
}

int main() {
    LinkedList* head = NULL;
    head = appendList(head, 'A');
    head = appendList(head, 'B');
    head = appendList(head, 'C');
    head = appendList(head, 'D');
    head = appendList(head, 'E');
    showList(head);
    head = reverseList(head);
    showList(head);
    return 0;
}