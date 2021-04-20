#include "guiManager.h"
#include "OpenGL.h"
#include "Physics/physicsInterface.h"
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

typedef struct menuOption {
    bool menu, level, settings, exit, developer;
} menuOption;

struct GuiContainer {
    struct nk_context *ctx;
    struct nk_font_atlas *atlas;
    menuOption options;
    bool inGame;
    int height;
    int width;
    int gravity;
    bool debug;
} GuiContainer;

void GuiManager_init() {
    //Font
    struct nk_font *myFont = NULL;
    float fontSize = 24;
    struct nk_font_config cfg1 = nk_font_config(fontSize);

    /* GUI */
    GuiContainer.ctx = nk_glfw3_init(engine.window, NK_GLFW3_INSTALL_CALLBACKS);
    nk_glfw3_font_stash_begin(&GuiContainer.atlas);
    //Load font
    myFont = nk_font_atlas_add_default(GuiContainer.atlas, fontSize, &cfg1);
    //Load cursor
    nk_style_load_all_cursors(GuiContainer.ctx, GuiContainer.atlas->cursors);
    nk_glfw3_font_stash_end();

    //Set font
    nk_style_set_font(GuiContainer.ctx, &myFont->handle);

    GuiManager_optionsReset();
    GuiContainer.options.menu = true;
    GuiContainer.inGame = false;
    GuiContainer.gravity = -1;
    GuiContainer.debug = false;
}

void GuiManager_update() {
    glfwGetWindowSize(engine.window, &GuiContainer.width, &GuiContainer.height);
}

void GuiManager_levelMenu() {
    glfwPollEvents();
    nk_glfw3_new_frame();

    /* GUI */
    if (nk_begin(GuiContainer.ctx, "Big Balls Roll!", nk_rect(50, 50, (float) GuiContainer.width/3, (float) GuiContainer.height /2.5f),
                 NK_WINDOW_BORDER|NK_WINDOW_TITLE)) {

        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 1);
        nk_label(GuiContainer.ctx, "NEW GAME", NK_TEXT_CENTERED);
        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 6);
        if (nk_button_label(GuiContainer.ctx, "MAIN MENU")) {
            GuiManager_optionsReset();
            GuiContainer.options.menu = true;
        }

        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 10, 1);

        //Name
        if (nk_group_begin(GuiContainer.ctx, "Name",  NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_edit_string(GuiContainer.ctx, NK_EDIT_FIELD | NK_EDIT_GOTO_END_ON_ACTIVATE, engine.playerConfig.name, &engine.playerConfig.nameLength, 256, nk_filter_ascii);

            nk_group_end(GuiContainer.ctx);
        }

        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 8, 1);
        //Level
        if (nk_group_begin(GuiContainer.ctx, "Level",  NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_property_int(GuiContainer.ctx, "Seed:", INT_MIN, &engine.playerConfig.seed, INT_MAX, 10, 10);

            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_property_int(GuiContainer.ctx, "Total levels:", 1, &engine.playerConfig.levels, 20, 1, 10);

            nk_group_end(GuiContainer.ctx);
        }

        //Confirm button
        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 1);
        if (nk_button_label(GuiContainer.ctx, "LET EM' ROLL!")) {
            GuiContainer.inGame = true;
            //TODO:: pass the stuff
            printf("name: %s\n", engine.playerConfig.name);
            printf("Seed: %i\n", engine.playerConfig.seed);
            printf("Levels: %i\n", engine.playerConfig.levels);
        }

    }
    nk_end(GuiContainer.ctx);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

void GuiManager_settingsMenu() {
    glfwPollEvents();
    nk_glfw3_new_frame();

    /* GUI */
    if (nk_begin(GuiContainer.ctx, "Big Balls Roll!", nk_rect(50, 50, (float) GuiContainer.width/3, (float) GuiContainer.height/1.5f),
                 NK_WINDOW_BORDER|NK_WINDOW_TITLE)) {

        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 1);
        nk_label(GuiContainer.ctx, "SETTINGS", NK_TEXT_CENTERED);
        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 6);
        if (nk_button_label(GuiContainer.ctx, "MAIN MENU")) {
            GuiManager_optionsReset();
            GuiContainer.options.menu = true;
        }
        nk_label(GuiContainer.ctx, "", NK_TEXT_CENTERED);
        nk_label(GuiContainer.ctx, "", NK_TEXT_CENTERED);
        nk_label(GuiContainer.ctx, "", NK_TEXT_CENTERED);
        nk_label(GuiContainer.ctx, "", NK_TEXT_CENTERED);
        if (nk_button_label(GuiContainer.ctx, "DEVELOPER")) {
            GuiManager_optionsReset();
            GuiContainer.options.developer = true;
        }

        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 7, 1);

        //Window settings
        if (nk_group_begin(GuiContainer.ctx, "Window", NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_property_int(GuiContainer.ctx, "Width:", 1280, &engine.playerConfig.width, 3840, 100, 10);
            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_property_int(GuiContainer.ctx, "Height:", 720, &engine.playerConfig.height, 2160, 100, 10);
            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_label(GuiContainer.ctx, "Windowed mode: ", NK_TEXT_LEFT);
            if (nk_option_label(GuiContainer.ctx, "Enabled", engine.playerConfig.windowedMode == true)) engine.playerConfig.windowedMode = true;
            if (nk_option_label(GuiContainer.ctx, "Disabled", engine.playerConfig.windowedMode == false)) engine.playerConfig.windowedMode = false;
            nk_group_end(GuiContainer.ctx);
        }

        nk_layout_row_dynamic(GuiContainer.ctx, (float) engine.height / 8, 1);

        //Audio settings
        if (nk_group_begin(GuiContainer.ctx, "Audio", NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_property_int(GuiContainer.ctx, "Volume:", 0, &engine.playerConfig.volume, 100, 10, 10);
            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_label(GuiContainer.ctx, "Sound: ", NK_TEXT_LEFT);
            if (nk_option_label(GuiContainer.ctx, "Enabled", engine.playerConfig.sound == true)) engine.playerConfig.sound = true;
            if (nk_option_label(GuiContainer.ctx, "Disabled", engine.playerConfig.sound == false)) engine.playerConfig.sound = false;
            nk_group_end(GuiContainer.ctx);
        }

        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 4.7f, 1);

        //Mouse settings
        if (nk_group_begin(GuiContainer.ctx, "Mouse", NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_label(GuiContainer.ctx, "Sensitivity: ", NK_TEXT_LEFT);
            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_property_int(GuiContainer.ctx, "Vertical:", 0, &engine.playerConfig.verticalSens, 100, 10, 10);
            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_property_int(GuiContainer.ctx, "Horizontal:", 0, &engine.playerConfig.horizontalSens, 100, 10, 10);

            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_label(GuiContainer.ctx, "Horizontal lock: ", NK_TEXT_LEFT);
            if (nk_option_label(GuiContainer.ctx, "Enabled", engine.playerConfig.horizontalLock == true)) engine.playerConfig.horizontalLock = true;
            if (nk_option_label(GuiContainer.ctx, "Disabled", engine.playerConfig.horizontalLock == false)) engine.playerConfig.horizontalLock = false;
            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 1);
            nk_label(GuiContainer.ctx, "When enabled you must right click to pan the camera.", NK_TEXT_LEFT);
            nk_group_end(GuiContainer.ctx);
        }

        //Confirm button
        nk_layout_row_dynamic(GuiContainer.ctx, (float) (float)GuiContainer.height / 32, 1);
        if (nk_button_label(GuiContainer.ctx, "Confirm")) {
            //TODO:: pass the stuff
            printf("Volume: %i\n", engine.playerConfig.volume);
            printf("sound: %i\n", engine.playerConfig.sound);
            printf("V sens: %i\n", engine.playerConfig.verticalSens);
            printf("H sens: %i\n", engine.playerConfig.horizontalSens);
            printf("H Lock: %i\n", engine.playerConfig.horizontalLock);
        }
    }
    nk_end(GuiContainer.ctx);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

void GuiManager_developerMenu() {
    glfwPollEvents();
    nk_glfw3_new_frame();

    /* GUI */
    if (nk_begin(GuiContainer.ctx, "Big Balls Roll!", nk_rect(50, 50, (float) GuiContainer.width/3, (float) GuiContainer.height/3),
                 NK_WINDOW_BORDER|NK_WINDOW_TITLE)) {

        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 1);
        nk_label(GuiContainer.ctx, "DEVELOPER SETTINGS", NK_TEXT_CENTERED);
        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 6);
        if (nk_button_label(GuiContainer.ctx, "MAIN MENU")) {
            GuiManager_optionsReset();
            GuiContainer.options.menu = true;
        }
        nk_label(GuiContainer.ctx, "", NK_TEXT_CENTERED);
        nk_label(GuiContainer.ctx, "", NK_TEXT_CENTERED);
        nk_label(GuiContainer.ctx, "", NK_TEXT_CENTERED);
        nk_label(GuiContainer.ctx, "", NK_TEXT_CENTERED);
        if (nk_button_label(GuiContainer.ctx, "SETTINGS")) {
            GuiManager_optionsReset();
            GuiContainer.options.settings = true;
        }

        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 7, 1);

        //Physics settings
        if (nk_group_begin(GuiContainer.ctx, "Physics", NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_property_int(GuiContainer.ctx, "Gravity:", -100, &GuiContainer.gravity, 100, 1, 10);
            nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 3);
            nk_label(GuiContainer.ctx, "Debug Render: ", NK_TEXT_LEFT);
            if (nk_option_label(GuiContainer.ctx, "Enabled", GuiContainer.debug == true)) GuiContainer.debug = true;
            if (nk_option_label(GuiContainer.ctx, "Disabled", GuiContainer.debug == false)) GuiContainer.debug = false;
            nk_group_end(GuiContainer.ctx);
        }

        //Confirm button
        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 1);
        if (nk_button_label(GuiContainer.ctx, "Confirm")) {
            //TODO:: pass the stuff
            printf("Gravity: %i\n", GuiContainer.gravity);
            printf("Debug: %i\n", GuiContainer.debug);
        }
    }
    nk_end(GuiContainer.ctx);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

void GuiManager_mainMenu() {
    glfwPollEvents();
    nk_glfw3_new_frame();

    /* GUI */
    if (nk_begin(GuiContainer.ctx, "Big Balls Roll!", nk_rect(50, 50, (float) GuiContainer.width/3, (float) GuiContainer.height/5),
                 NK_WINDOW_BORDER|NK_WINDOW_TITLE)) {

        //Menu title
        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 1);
        nk_label(GuiContainer.ctx, "MAIN MENU", NK_TEXT_CENTERED);

        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 1);
        if (nk_button_label(GuiContainer.ctx, "NEW GAME")) {
            GuiManager_optionsReset();
            GuiContainer.options.level = true;
        }

        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 1);
        if (nk_button_label(GuiContainer.ctx, "SETTINGS")) {
            GuiManager_optionsReset();
            GuiContainer.options.settings = true;
        }

        //Quit
        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 1);
        if (nk_button_label(GuiContainer.ctx, "EXIT")) {
            GuiManager_optionsReset();
            GuiContainer.options.exit = true;
        }
    }
    nk_end(GuiContainer.ctx);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

void GuiManager_gameMenu() {
    glfwPollEvents();
    nk_glfw3_new_frame();

    /* GUI */
    if (nk_begin(GuiContainer.ctx, "Big Balls Roll!", nk_rect(50, 50, (float) GuiContainer.width/3, (float) GuiContainer.height/5),
                 NK_WINDOW_BORDER|NK_WINDOW_TITLE)) {

        //Menu title
        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 1);
        nk_label(GuiContainer.ctx, "GAME MENU", NK_TEXT_CENTERED);

        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 1);
        if (nk_button_label(GuiContainer.ctx, "SETTINGS")) {
            GuiManager_optionsReset();
            GuiContainer.options.settings = true;
        }

        //EXIT
        nk_layout_row_dynamic(GuiContainer.ctx, (float) GuiContainer.height / 32, 1);
        if (nk_button_label(GuiContainer.ctx, "QUIT")) {
            GuiManager_optionsReset();
            GuiContainer.options.menu = true;
            GuiContainer.inGame = false;
        }
    }
    nk_end(GuiContainer.ctx);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

void GuiManager_optionsReset()  {
    GuiContainer.options.level = false;
    GuiContainer.options.menu = false;
    GuiContainer.options.exit = false;
    GuiContainer.options.settings = false;
    GuiContainer.options.developer = false;
}

void GuiManager_draw() {
    GuiManager_update();
    if (GuiContainer.options.level) {
        GuiManager_levelMenu();
    } else if (GuiContainer.options.settings) {
        GuiManager_settingsMenu();
    } else if (GuiContainer.options.menu) {
        if(GuiContainer.inGame) {
            GuiManager_gameMenu();
        } else {
            GuiManager_mainMenu();
        }
    } else if (GuiContainer.options.developer) {
        GuiManager_developerMenu();
    } else if (GuiContainer.options.exit) {
        Engine_stop();//TODO:: add exit screen
    }
}

void GuiManager_free() {
    nk_glfw3_shutdown();
}
