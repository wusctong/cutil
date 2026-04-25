#include "plug.c"

#define CN_FONT_PATH "SourceHanSerifSC-VF.ttf"

int main(void) {
    InitWindow(800, 600, "Class Utility");
    SetTargetFPS(60);
    SetRandomSeed((unsigned int)time(NULL));

    int cpCount = 0;
    int* codepoints = build_cjk_codepoints(&cpCount);
    Font cn_font = LoadFontEx(CN_FONT_PATH, 40, codepoints, cpCount);
    free(codepoints);

    Grid root = {{300, 200}, {100}};
    Element run = {1,
                   0,
                   "RUN",
                   2.0f,
                   10.0f,
                   40.0f,
                   2.0f,
                   BLACK,
                   WHITE,
                   BLACK,
                   {10, 10, 10, 10},
                   GetFontDefault()};
    Element res = {0,     0,     "...",        0,      0, 60.0f, 2.0f, WHITE,
                   WHITE, BLACK, {0, 0, 0, 0}, cn_font};

    Node* class = create_nodes(
        {"曹萌哲", 1}, {"陈清扬", 2}, {"陈思涵", 3}, {"丁子洵", 4},
        {"顾锦海", 5}, {"蒋力", 6}, {"焦澄杨", 7}, {"金鑫", 8}, {"林诺", 9},
        {"马亦铭", 10}, {"潘昊俊", 11}, {"沈逸欣", 12}, {"宋欣辰", 13},
        {"汤炜博", 14}, {"王昊天", 15}, {"卫陈昕", 16}, {"吴曈", 17},
        {"杨艾橦", 18}, {"杨子懿", 19}, {"尤书涵", 20}, {"于一晨", 21},
        {"袁宇轩", 22}, {"詹圣泽", 23}, {"何珈霖", 24}, {"李若绮", 25},
        {"李思妍", 26}, {"刘梦涵", 27}, {"钱奕轩", 28}, {"钱玥辰", 29},
        {"邵逸可", 30}, {"王璨奕", 31}, {"邬慕瑶", 32}, {"吴歆雅", 33},
        {"奚贝拉", 34}, {"项茜", 35}, {"杨沈奕", 36}, {"张敬涵", 37},
        {"张洛瑶", 38}, {"张雯萱", 39}, {"周昕妤", 40}, {"朱可馨", 41},
        {"王佳琪", 42}, {"杨孝恒", 43}, {"俞闵亮", 44}, {"裴冉", 45});
    Node* rp = go_node(class, 0);

    resize_window(root);

    while (!WindowShouldClose()) {
        if (is_element_pressed(MOUSE_BUTTON_LEFT, run, root)) {
            rp = get_random_node(class);
            res.text = strdup(TextFormat("%d %s", rp->num, rp->name));
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
