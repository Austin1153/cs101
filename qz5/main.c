#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int head;
    struct node* next;
} node_t;

node_t* allocate_node(int data) {
    node_t* last = (node_t*)calloc(1,sizeof(node_t));
    last->head = data;
    return last;
}

void show_list(node_t* list) {
    while (list->head) {
        printf("[%d]->", list->head);
        list = list->next;
    }
    printf("null");
}

node_t* append_node(node_t* list, int new_data) {
    node_t* tmp = list;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    if (*(tmp->head) == NULL) {
        tmp->head = new_data;
    } else {
        tmp->next = allocate_node(new_data);
    }
    return list;
}

void free_all_node(node_t* list) {

}

int main() {
    node_t* head = NULL;
    head = append_node(head, 0);
    show_list(head);
    head = append_node(head, 11);
    show_list(head);
    head = append_node(head, 222);
    show_list(head);
    head = append_node(head, 3333);
    show_list(head);
    // free_all_node(head);
    return 0;
}