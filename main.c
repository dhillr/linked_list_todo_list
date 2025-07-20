#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char* data;
    void* next;
} node;

typedef struct {
    node* head;
} linked_list;

linked_list gen_linked_list() {
    return (linked_list){.head=NULL};
}

void add_item(char* item, linked_list* list) {
    node* ptr = list->head;
    
    node* itemPtr = malloc(sizeof(node));
    memcpy(itemPtr, &(node){
        .data=item,
        .next=NULL
    }, sizeof(node));

    if (ptr) {
        while (ptr->next) ptr = ptr->next;
    } else {
        list->head = itemPtr;   
        return;
    }

    ptr->next = itemPtr;
}

void print_list(linked_list list) {
    node* ptr = list.head;
    int i = 0;
    if (!ptr) return;

    while (ptr) {
        printf("\033[31m%d. \033[33m%s\n", i + 1, ptr->data);
        ptr = ptr->next;
        i++;
    }
    printf("\033[0m");
}

void delete_item(size_t index, linked_list* list) {
    node* ptr = list->head;
    node* prev = NULL;

    int i = 0;
    while (ptr && i < index) {
        prev = ptr;
        ptr = ptr->next;
        i++;
    }
    
    if (!ptr) return;

    if (prev)
        prev->next = ptr->next;
    else
        list->head = ptr->next;
    
    free(ptr);
}

void free_list(linked_list* list) {
    node* ptr = list->head;

    while (ptr) {
        node* next = ptr->next;
        free(ptr);
        ptr = next;
    }

    list->head = NULL;
}

int equals(char* a, char* b, int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

int main() {
    linked_list list = gen_linked_list();

    // delete_item(0, &list);

    while (1) {
        char* argc = malloc(3);
        printf("\033[0mWhat would you like to do? (add, del, lst, ext) \033[0;32m>>> \033[33m");
        scanf("%s", argc);
        printf("\033[0m");

        if (equals(argc, "add", 3)) {
            char* item = malloc(512);

            printf("What would you like to add? \033[0;32m>>> \033[33m");
            scanf("%s", item);

            add_item(item, &list);
        } else if (equals(argc, "del", 3)) {
            int index;

            printf("What is the index of the item you want to delete? \033[0;32m>>> \033[33m");
            scanf("%d", &index);

            delete_item(index - 1, &list);
        } else if (equals(argc, "lst", 3)) {
            print_list(list);
        } else if (equals(argc, "ext", 3)) {
            printf("\033[0m");
            break;
        }
    }

    free_list(&list);

    return 0;
}