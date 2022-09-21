#include <stdio.h>
#include <stdlib.h>

struct node {
    int head;
    struct node* next;
};
typedef struct node node_t;

node_t* allocate_node(int data) {
    node_t* last = (node_t*)calloc(1,sizeof(node_t));
    last->head = data;
    return last;
}

void show_list(node_t* list) {
    while (list->next) {
        printf("[%d]->", list->head);
        list = list->next;
    }
    printf("[%d]->", list->head);
    printf("null\n");
}

node_t* append_node(node_t* list, int new_data) {
    node_t* tmp = list;
    if (list == NULL) {
        list = allocate_node(new_data);
        return list;
    }
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = allocate_node(new_data);
    return list;
}

void free_all_node(node_t* list) {
    node_t* tmp;
    while(list->next) {
        tmp = list->next;
        printf("free([%d])->", list->head);
        free(list);
        list = tmp;
    }
    printf("free([%d])->", list->head);
    free(list);
    printf("null\n");
}

node_t* add_node(node_t* head, int new_data) {
    node_t* first = allocate_node(new_data);
    first->next = head;
    return first;
}

node_t* del_node(node_t* head, int n) {
    node_t* new, *del;
    new = head;
    if (n == 0) {
        new = head->next;
        del = head;
        free(del);
        return new;
    }
    for (int i = 1; i < n; i++) {
        new = new->next;
    }
    del = new->next;
    new->next = del->next;
    free(del);
    return head; 
}

int main() {
    node_t* head = NULL;
    head = append_node(head, 0);
    show_list(head);
    head = append_node(head, 1);
    show_list(head);
    head = add_node(head, -1);
    show_list(head);
    head = del_node(head, 1);
    show_list(head);
    free_all_node(head);
    return 0;
} 
