#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    char* name;
    int num;
    struct Node* next;
} Node;

typedef struct {
    char* name;
    int num;
} NodeArg;

Node* go_node(Node* head, size_t depth) {
    for (size_t i = 0; i < depth && head != NULL; i++) {
        head = head->next;
    }
    return head;
}

void free_node(Node* n) {
    if (!n) return;
    free(n->name);
    free(n);
}

void free_nodes(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

size_t get_nodes_length(Node* head) {
    size_t len = 0;
    while (head) {
        head = head->next;
        len++;
    }
    return len;
}

Node* get_random_node(Node* head) {
    size_t len = get_nodes_length(head);
    return go_node(head, GetRandomValue(0, len - 1));
}

Node* create_nodes_impl(size_t count, NodeArg args[]) {
    if (count == 0) return NULL;

    Node *head = NULL, *tail = NULL;
    for (size_t i = 0; i < count; i++) {
        Node* new = malloc(sizeof(Node));
        new->name = args[i].name;
        new->num = args[i].num;
        new->next = NULL;

        if (!head)
            head = new;
        else
            tail->next = new;
        tail = new;
    }

    return head;
}

#define create_nodes(...)                                          \
    create_nodes_impl(                                             \
        (int)(sizeof((NodeArg[]){__VA_ARGS__}) / sizeof(NodeArg)), \
        (NodeArg[]){__VA_ARGS__})
