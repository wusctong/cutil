#include <raylib.h>
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
Node n3 = {"WT", 3, NULL};
Node n2 = {"YXH", 2, &n3};
Node n1 = {"CMZ", 1, &n2};

Node* go_node(Node* head, size_t depth) {
    for (size_t i = 0; i < depth && head != NULL; i++) {
        head = head->next;
    }
    return head;
}

size_t get_nodes_length(Node* head) {
    size_t len = 0;
    while (head != NULL) {
        head = head->next;
        len++;
    }
    return len;
}

Node* get_random_node(Node* head) {
    size_t len = get_nodes_length(head);
    return go_node(head, GetRandomValue(0, len - 1));
}
