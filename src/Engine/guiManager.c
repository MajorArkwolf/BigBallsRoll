#include "guiManager.h"
#include "OpenGL.h"
#include <Engine/engine.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL2_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "Engine/nuklear.h"
#include "Engine/nuklear_glfw_gl2.h"

struct GuiContainer { //TODO: find out what else I need // Global for now
    struct nk_context *ctx;
    struct nk_font_atlas *atlas;
} GuiContainer;

void guiManager_init() {
    /* GUI */
    GuiContainer.ctx = nk_glfw3_init(engine.window, NK_GLFW3_INSTALL_CALLBACKS);
    /* Load Fonts: if none of these are loaded a default font will be used  */
    /* Load Cursor: if you uncomment cursor loading please hide the cursor */

    nk_glfw3_font_stash_begin(&GuiContainer.atlas);
    nk_glfw3_font_stash_end();
}

void guiManager_mainMenu() {
    glfwPollEvents();
    nk_glfw3_new_frame();

    /* GUI */
    if (nk_begin(GuiContainer.ctx, "Big Balls Roll!", nk_rect(50, 50, engine.width/4, engine.height/2),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|NK_WINDOW_TITLE)) {

        //Menu title
        nk_layout_row_dynamic(GuiContainer.ctx, engine.height / 32, 1);
        nk_label(GuiContainer.ctx, "Menu: ", NK_TEXT_LEFT);

        nk_layout_row_dynamic(GuiContainer.ctx, engine.height / 13, 1);

        //Level settings
        if (nk_group_begin(GuiContainer.ctx, "Level",  NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(GuiContainer.ctx, engine.height / 32, 3);
            nk_property_int(GuiContainer.ctx, "Seed:", INT_MIN, &engine.playerConfig.seed, INT_MAX, 10, 10);

            nk_group_end(GuiContainer.ctx);
        }

        nk_layout_row_dynamic(GuiContainer.ctx, engine.height / 8, 1);

        //Audio settings
        if (nk_group_begin(GuiContainer.ctx, "Audio", NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(GuiContainer.ctx, engine.height / 32, 3);
            nk_property_int(GuiContainer.ctx, "Volume:", 0, &engine.playerConfig.volume, 100, 10, 10);
            nk_layout_row_dynamic(GuiContainer.ctx, engine.height / 32, 3);
            nk_label(GuiContainer.ctx, "Sound: ", NK_TEXT_LEFT);
            if (nk_option_label(GuiContainer.ctx, "Enabled", engine.playerConfig.sound == true)) engine.playerConfig.sound = true;
            if (nk_option_label(GuiContainer.ctx, "Disabled", engine.playerConfig.sound == false)) engine.playerConfig.sound = false;
            nk_group_end(GuiContainer.ctx);
        }

        nk_layout_row_dynamic(GuiContainer.ctx, engine.height / 6, 1);

        //Mouse settings
        if (nk_group_begin(GuiContainer.ctx, "Mouse", NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(GuiContainer.ctx, engine.height / 32, 3);
            nk_label(GuiContainer.ctx, "Sensitivity: ", NK_TEXT_LEFT);
            nk_layout_row_dynamic(GuiContainer.ctx, engine.height / 32, 3);
            nk_property_int(GuiContainer.ctx, "Vertical:", 0, &engine.playerConfig.verticalSens, 100, 10, 10);
            nk_layout_row_dynamic(GuiContainer.ctx, engine.height / 32, 3);
            nk_property_int(GuiContainer.ctx, "Horizontal:", 0, &engine.playerConfig.horizontalSens, 100, 10, 10);
            nk_group_end(GuiContainer.ctx);
        }

        //Confirm button
        nk_layout_row_dynamic(GuiContainer.ctx, engine.height / 32, 1);
        if (nk_button_label(GuiContainer.ctx, "Confirm")) {
            //TODO:: pass the stuff
            printf("Seed: %i\n", engine.playerConfig.seed);
            printf("Volume: %i\n", engine.playerConfig.volume);
            printf("sound: %i\n", engine.playerConfig.sound);
            printf("V sens: %i\n", engine.playerConfig.verticalSens);
            printf("H sens: %i\n", engine.playerConfig.horizontalSens);
        }
    }
    nk_end(GuiContainer.ctx);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

void guiManager_free() {
    nk_glfw3_shutdown();
}
