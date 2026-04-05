#include <raylib.h>

#include "plug.c"

int main(void) {
    InitWindow(800, 600, "Class Utility");
    SetTargetFPS(60);
    SetRandomSeed((unsigned int)time(NULL));
    Node* class = create_nodes({"CMZ", 1}, {"YXH", 2}, {"WT", 3});
    Node* rp = go_node(class, 0);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) rp = get_random_node(class);

        ClearBackground(WHITE);
        BeginDrawing();
        DrawText(TextFormat("%s %d", rp->name, rp->num), 10, 10, 50, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
