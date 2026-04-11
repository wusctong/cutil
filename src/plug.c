#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ROW 1024
#define MAX_COLUMN 1024

// Data
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

// Render
typedef struct {
    size_t l, r, u, d;
} Padding;

typedef struct {
    size_t width[MAX_COLUMN];
    size_t height[MAX_ROW];
} Grid;

typedef struct {
    size_t column, row;
    char* text;
    float border_width, radius, font_size, spacing;
    Color border_color, bg_color, fg_color;
    Padding padding;
} Element;

void resize_window(Grid g) {
    int width = 0, height = 0;
    for (int i = 0; g.width[i] > 0; i++) width += g.width[i];
    for (int i = 0; g.height[i] > 0; i++) height += g.height[i];
    SetWindowSize(width, height);
}

Vector2 get_element_pos(Element e, Grid g) {
    Vector2 r = {0, 0};
    for (size_t i = 0; i < e.column; i++) r.x += g.width[i];
    for (size_t i = 0; i < e.row; i++) r.y += g.height[i];
    r.x += e.padding.l;
    r.y += e.padding.u;
    return r;
}

bool is_element_pressed(int mouse_button, Element e, Grid g) {
    Vector2 pos = get_element_pos(e, g);
    int mouse_x = GetMouseX(), mouse_y = GetMouseY();
    return (IsMouseButtonPressed(mouse_button) && mouse_x >= pos.x &&
            mouse_x <= pos.x + g.width[e.column] && mouse_y >= pos.y &&
            mouse_y <= pos.y + g.height[e.row]);
}

void draw_element(Element e, Grid g) {
    Vector2 pos = get_element_pos(e, g);
    float width = g.width[e.column] - e.padding.l - e.padding.r;
    float height = g.height[e.row] - e.padding.u - e.padding.d;

    Rectangle border = {pos.x, pos.y, width, height};
    Rectangle bg = {pos.x + e.border_width, pos.y + e.border_width,
                    width - (e.border_width * 2),
                    height - (e.border_width * 2)};

    float outer_radius = e.radius;
    float inner_radius = outer_radius - e.border_width;
    if (inner_radius < 0) inner_radius = 0;
    float outer_roundness =
        (outer_radius * 2.0f) / (width < height ? width : height);
    float inner_roundness =
        (inner_radius * 2.0f) / (bg.width < bg.height ? bg.width : bg.height);

    DrawRectangleRounded(border, outer_roundness, 10, e.border_color);
    DrawRectangleRounded(bg, inner_roundness, 10, e.bg_color);

    Font font = GetFontDefault();
    Vector2 textSize = MeasureTextEx(font, e.text, e.font_size, e.spacing);
    Vector2 textPos = {bg.x + (bg.width / 2) - (textSize.x / 2),
                       bg.y + (bg.height / 2) - (textSize.y / 2)};

    DrawTextEx(font, e.text, textPos, e.font_size, e.spacing, e.fg_color);
}
