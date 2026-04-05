#include <raylib.h>

#include "plug.c"

int main(void) {
    InitWindow(800, 600, "Class Utility");
    SetTargetFPS(60);
    SetRandomSeed((unsigned int)time(NULL));
    Node* rp = &n1;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) rp = get_rp(&n1);

        ClearBackground(WHITE);
        BeginDrawing();
        DrawText(TextFormat("%s %d", rp->name, rp->num), 10, 10, 50, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
