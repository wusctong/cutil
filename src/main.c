#include <raylib.h>

#include "plug.c"

#define CN_FONT_PATH "font.ttf"
#define CONFIG_PATH "config.txt"
#define CLASS_FILE_PATH "names.txt"

int main(void) {
    InitWindow(800, 600, "Class Utility");
    SetTargetFPS(60);
    SetRandomSeed((unsigned int)time(NULL));

    int cpCount = 0;
    int* codepoints = build_cjk_codepoints(&cpCount);
    Font cn_font = LoadFontEx(CN_FONT_PATH, 40, codepoints, cpCount);
    free(codepoints);

    Config conf = read_config(CONFIG_PATH);
    if (conf.scale == 0) conf.scale = 100;

    // Menu
    Grid g_menu = {{4 * conf.scale}, {conf.scale, conf.scale}};
    Element e_rand_ppl = {
        .column = 0,
        .row = 0,
        .text = "随机抽人",
        .border_width = 2.0f,
        .radius = 10.0f,
        .font_size = 0.6 * conf.scale,
        .spacing = 2.0f,
        .border_color = BLACK,
        .bg_color = WHITE,
        .fg_color = BLACK,
        .padding = {10, 10, 10, 10},
        .font = cn_font,
    };
    Element e_nodepad = {
        .column = 0,
        .row = 1,
        .text = "笔记板",
        .border_width = 2.0f,
        .radius = 10.0f,
        .font_size = 0.6 * conf.scale,
        .spacing = 2.0f,
        .border_color = BLACK,
        .bg_color = WHITE,
        .fg_color = BLACK,
        .padding = {10, 10, 10, 10},
        .font = cn_font,
    };

    // Random People
    Grid g_rand_ppl = {{conf.scale, 3 * conf.scale, 2 * conf.scale},
                       {conf.scale}};
    Element e_rand_ppl_res = {
        .column = 1,
        .row = 0,
        .text = strdup("..."),
        .border_width = 0,
        .radius = 0,
        .font_size = 0.6f * conf.scale,
        .spacing = 2.0f,
        .border_color = WHITE,
        .bg_color = WHITE,
        .fg_color = BLACK,
        .padding = {0, 0, 0, 0},
        .font = cn_font,
    };
    Node* class = create_nodes_from_file(CLASS_FILE_PATH);
    if (class == NULL) {
        class = create_nodes(
            {"曹萌哲", 1}, {"陈清扬", 2}, {"陈思涵", 3}, {"丁子洵", 4},
            {"顾锦海", 5}, {"蒋力", 6}, {"焦澄杨", 7}, {"金鑫", 8}, {"林诺", 9},
            {"马亦铭", 10}, {"潘昊俊", 11}, {"沈逸欣", 12}, {"宋欣辰", 13},
            {"汤炜博", 14}, {"王昊天", 15}, {"卫陈昕", 16}, {"吴曈", 17},
            {"杨艾橦", 18}, {"杨子懿", 19}, {"尤书涵", 20}, {"于一晨", 21},
            {"袁宇轩", 22}, {"詹圣泽", 23}, {"何珈霖", 24}, {"李若绮", 25},
            {"李思妍", 26}, {"刘梦涵", 27}, {"钱奕轩", 28}, {"钱玥辰", 29},
            {"邵逸可", 30}, {"王璨奕", 31}, {"王佳琪", 32}, {"邬慕瑶", 33},
            {"吴歆雅", 34}, {"奚贝拉", 35}, {"项茜", 36}, {"杨沈奕", 37},
            {"张敬涵", 38}, {"张洛瑶", 39}, {"张雯萱", 40}, {"周昕妤", 41},
            {"朱可馨", 42}, {"杨孝恒", 43}, {"严伟宁", 44}, {"俞闵亮", 44},
            {"裴冉", 45});
    }
    Node* rp = go_node(class, 0);

    // Notepad
    Grid g_notepad = {{5 * conf.scale}, {1 * conf.scale, 5 * conf.scale}};
    Element e_notepad_pad = {0,
                             1,
                             "",
                             2.0f,
                             10.0f,
                             40.0f,
                             2.0f,
                             BLACK,
                             WHITE,
                             BLACK,
                             {10, 10, 10, 10},
                             GetFontDefault()};

    // Global
    Grid* g_ptr = &g_menu;
    Element e_back = {.column = 0,
                      .row = 0,
                      .text = "<",
                      .border_width = 2.0f,
                      .radius = 10.0f,
                      .font_size = 0.6 * conf.scale,
                      .spacing = 2.0f,
                      .border_color = BLACK,
                      .bg_color = WHITE,
                      .fg_color = BLACK,
                      .padding = {10, 10, 10, 10},
                      .font = GetFontDefault()};
    Element e_run = {.column = 2,
                     .row = 0,
                     .text = "RUN",
                     .border_width = 2.0f,
                     .radius = 10.0f,
                     .font_size = 0.4 * conf.scale,
                     .spacing = 2.0f,
                     .border_color = BLACK,
                     .bg_color = WHITE,
                     .fg_color = BLACK,
                     .padding = {10, 10, 10, 10},
                     .font = GetFontDefault()};

    resize_window(*g_ptr);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        if (g_ptr == &g_menu) {
            if (is_element_pressed(MOUSE_BUTTON_LEFT, e_rand_ppl, g_menu)) {
                g_ptr = &g_rand_ppl;
                resize_window(*g_ptr);
            } else if (is_element_pressed(MOUSE_BUTTON_LEFT, e_nodepad,
                                          g_menu)) {
                g_ptr = &g_notepad;
                resize_window(*g_ptr);
            }
        } else {
            if (is_element_pressed(MOUSE_BUTTON_LEFT, e_back, *g_ptr)) {
                g_ptr = &g_menu;
                resize_window(*g_ptr);
            }
            if (g_ptr == &g_rand_ppl) {
                if (is_element_pressed(MOUSE_BUTTON_LEFT, e_run, g_rand_ppl)) {
                    rp = get_random_node(class);
                    free(e_rand_ppl_res.text);
                    e_rand_ppl_res.text =
                        strdup(TextFormat("%d %s", rp->num, rp->name));
                }
            }
        }

        if (g_ptr == &g_menu) {
            draw_element(e_rand_ppl, *g_ptr);
            draw_element(e_nodepad, *g_ptr);
        } else if (g_ptr == &g_rand_ppl) {
            draw_element(e_back, *g_ptr);
            draw_element(e_rand_ppl_res, *g_ptr);
            draw_element(e_run, *g_ptr);
        } else if (g_ptr == &g_notepad) {
            draw_element(e_back, *g_ptr);
            draw_element(e_notepad_pad, *g_ptr);
        }
        EndDrawing();
    }

    UnloadFont(cn_font);
    free(e_rand_ppl_res.text);
    free_nodes(class);

    CloseWindow();
    return 0;
}
