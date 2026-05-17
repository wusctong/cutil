#include "plug.c"

#define EXTERN_FONT_PATH "font.ttf"
#define CONFIG_PATH "config.txt"
#define NAME_LIST_PATH "names.txt"

#define KEY_RELOAD KEY_R

#define MAX_FONT_SIZE 70

void load_name_list(Node** name_list, const char *fp) {
    Node* new_name_list = create_nodes_from_file(fp);
    if (new_name_list == NULL) return;
    free_nodes(*name_list);
    *name_list = new_name_list;
}

int main(void) {
    InitWindow(800, 600, "Class Utility");
    SetTargetFPS(60);
    SetRandomSeed((unsigned int)time(NULL));

    int cpCount = 0;
    int* codepoints = build_cjk_codepoints(&cpCount);
    Font extern_font =
        LoadFontEx(EXTERN_FONT_PATH, MAX_FONT_SIZE, codepoints, cpCount);
    free(codepoints);

    Config conf = read_config(CONFIG_PATH);
    if (conf.scale == 0) conf = (Config){.scale = 100, .ppl_count = 1};

    // Menu
    Grid g_menu = {{4 * conf.scale}, {conf.scale, conf.scale}};
    Element e_rand_ppl = {
        .column = 0,
        .row = 0,
        .text = "随机抽人",
        .border_width = 0.02f * conf.scale,
        .radius = 10.0f,
        .font_size = 0.6 * conf.scale,
        .spacing = 2.0f,
        .border_color = BLACK,
        .bg_color = WHITE,
        .fg_color = BLACK,
        .padding = {10, 10, 10, 10},
        .font = extern_font,
    };
    Element e_nodepad = {
        .column = 0,
        .row = 1,
        .text = "笔记板",
        .border_width = 0.02f * conf.scale,
        .radius = 10.0f,
        .font_size = 0.6 * conf.scale,
        .spacing = 2.0f,
        .border_color = BLACK,
        .bg_color = WHITE,
        .fg_color = BLACK,
        .padding = {10, 10, 10, 10},
        .font = extern_font,
    };

    // Random People
    Grid g_rand_ppl = {{conf.scale, 3 * conf.scale, conf.scale, conf.scale},
                       {conf.scale}};
    for (size_t i = 0; i < conf.ppl_count; i++) {
        g_rand_ppl.height[i] = conf.scale;
    }
    Element e_rand_ppl_res_tmp = {
        .column = 1,
        .row = 0,
        .text = strdup("..."),
        .border_width = 0,
        .radius = 0,
        .font_size = 0.7f * conf.scale,
        .spacing = 2.0f,
        .border_color = WHITE,
        .bg_color = WHITE,
        .fg_color = BLACK,
        .padding = {0, 0, 0, 0},
        .font = extern_font,
    };
    Node* name_list = create_nodes_from_file(NAME_LIST_PATH);
    if (name_list == NULL) {
        name_list = create_nodes(
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
    Node nobody = {
        .name = "...",
        .num = 0,
        .next = NULL,
    };
    Node** rp = malloc(conf.ppl_count * sizeof(Node*));
    for (size_t i = 0; i < conf.ppl_count; i++) rp[i] = &nobody;

    // Notepad
    Grid g_notepad = {{5 * conf.scale}, {1 * conf.scale, 5 * conf.scale}};
    Element e_notepad_pad = {
        .column = 0,
        .row = 1,
        .text = "",
        .border_width = 2.0f,
        .radius = 10.0f,
        .font_size = 40.0f,
        .spacing = 2.0f,
        .border_color = BLACK,
        .bg_color = WHITE,
        .fg_color = BLACK,
        .padding = {10, 10, 10, 10},
        .font = extern_font,
    };

    // Global
    Grid* g_ptr = &g_menu;
    Element e_back = {
        .column = 0,
        .row = 0,
        .text = "<",
        .border_width = 0.02f * conf.scale,
        .radius = 10.0f,
        .font_size = 0.6 * conf.scale,
        .spacing = 2.0f,
        .border_color = BLACK,
        .bg_color = WHITE,
        .fg_color = BLACK,
        .padding = {10, 10, 10, 10},
        .font = extern_font,
    };
    Element e_run = {
        .column = 2,
        .row = 0,
        .text = "抽",
        .border_width = 0.02f * conf.scale,
        .radius = 10.0f,
        .font_size = 0.6 * conf.scale,
        .spacing = 2.0f,
        .border_color = BLACK,
        .bg_color = WHITE,
        .fg_color = BLACK,
        .padding = {10, 10, 10, 10},
        .font = extern_font,
    };
    Element e_reload = {
        .column = 3,
        .row = 0,
        .text = "载",
        .border_width = 0.02f * conf.scale,
        .radius = 10.0f,
        .font_size = 0.6 * conf.scale,
        .spacing = 2.0f,
        .border_color = BLACK,
        .bg_color = WHITE,
        .fg_color = BLACK,
        .padding = {10, 10, 10, 10},
        .font = extern_font,
    };

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
                size_t name_list_len = get_nodes_length(name_list);
                size_t loop_count = (conf.ppl_count < name_list_len)
                                        ? conf.ppl_count
                                        : name_list_len;
                if (is_element_pressed(MOUSE_BUTTON_LEFT, e_run, g_rand_ppl)) {
                    for (size_t i = 0; i < loop_count; i++) {
                        rp[i] = get_random_node(name_list);
                        for (size_t j = 0; j < i; j++)
                            while (strcmp(rp[i]->name, rp[j]->name) == 0)
                                rp[i] = get_random_node(name_list);
                    }
                }
                if (is_element_pressed(MOUSE_BUTTON_LEFT, e_reload,
                                       g_rand_ppl)) {
                    for (size_t i = 0; i < loop_count; i++) rp[i] = &nobody;
                    load_name_list(&name_list, NAME_LIST_PATH);
                }
                if (IsFileDropped()) {
                    for (size_t i = 0; i < loop_count; i++) rp[i] = &nobody;
                    FilePathList df = LoadDroppedFiles();
                    load_name_list(&name_list, df.paths[0]);
                    UnloadDroppedFiles(df);
                }
            }
        }

        if (g_ptr == &g_menu) {
            draw_element(e_rand_ppl, *g_ptr);
            draw_element(e_nodepad, *g_ptr);
        } else if (g_ptr == &g_rand_ppl) {
            draw_element(e_back, *g_ptr);
            for (size_t i = 0; i < conf.ppl_count; i++)
                draw_element_override(
                    e_rand_ppl_res_tmp, 1, i,
                    TextFormat("%d %s", rp[i]->num, rp[i]->name), *g_ptr);
            draw_element(e_run, *g_ptr);
            draw_element(e_reload, *g_ptr);
        } else if (g_ptr == &g_notepad) {
            draw_element(e_back, *g_ptr);
            draw_element(e_notepad_pad, *g_ptr);
        }

        EndDrawing();
    }

    UnloadFont(extern_font);
    free(e_rand_ppl_res_tmp.text);
    free_nodes(name_list);

    CloseWindow();
    return 0;
}
