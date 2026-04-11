#include "plug.c"

int main(void) {
    InitWindow(800, 600, "Class Utility");
    SetTargetFPS(60);
    SetRandomSeed((unsigned int)time(NULL));

    Grid root = {{300, 200}, {100}};
    Element run = {1,    0,     "RUN", 2.0f,  10.0f,           40.0f,
                   2.0f, BLACK, WHITE, BLACK, {10, 10, 10, 10}};
    Element res = {0,    0,     "...", 0,     0,           60.0f,
                   2.0f, WHITE, WHITE, BLACK, {0, 0, 0, 0}};

    Node* class = create_nodes({"cmz", 1}, {"YXH", 2}, {"WT", 3});
    Node* rp = go_node(class, 0);

    resize_window(root);

    while (!WindowShouldClose()) {
        if (is_element_pressed(MOUSE_BUTTON_LEFT, run, root)) {
            rp = get_random_node(class);
            res.text = strdup(TextFormat("No.%d %s", rp->num, rp->name));
        }

        ClearBackground(WHITE);
        BeginDrawing();
        // DrawText(TextFormat("%s %d", rp->name, rp->num), 10, 10, 50, BLACK);
        draw_element(res, root);
        draw_element(run, root);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
