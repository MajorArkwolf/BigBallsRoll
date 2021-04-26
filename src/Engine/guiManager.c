#include "guiManager.h"
#include "OpenGL.h"
#include "Physics/physicsInterface.h"
#include "Scene/Game/game.h"
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

void GuiManager_init(GuiManager *guiManager) {
    assert(guiManager != NULL);
    //Font
    struct nk_font *myFont = NULL;
    float fontSize = 24;
    struct nk_font_config cfg1 = nk_font_config(fontSize);

    /* GUI */
    guiManager->ctx = nk_glfw3_init(engine.window, NK_GLFW3_INSTALL_CALLBACKS);

    nk_glfw3_font_stash_begin(&guiManager->atlas);
    //Load font
    myFont = nk_font_atlas_add_default(guiManager->atlas, fontSize, &cfg1);
    nk_glfw3_font_stash_end();

    //Set font
    nk_style_set_font(guiManager->ctx, &myFont->handle);

    //init height and width
    GuiManager_update(guiManager);

    //init menu options
    GuiManager_optionsReset(guiManager);
    //Set main menu to draw first
    guiManager->options.menu = true;
    guiManager->inGame = false;
    guiManager->guiDraw = false;
    guiManager->hud.prevLevel = 0;
    guiManager->hud.prevLives = 0;
    guiManager->hud.prevSeconds = 0.0f;
    guiManager->hud.updateHUD = false;

    //TODO:: TEMP
    guiManager->gravity = -1;
    guiManager->debug = false;
}

void GuiManager_update(GuiManager *guiManager) {
    assert(guiManager != NULL);
    glfwGetWindowSize(engine.window, &guiManager->glfwWidth, &guiManager->glfwHeight);
    GuiManager_setMenuPosition(guiManager,4 ,4);
}

void GuiManager_free(GuiManager *guiManager) {
    assert(guiManager != NULL);
    nk_glfw3_shutdown();
}

void GuiManager_drawToggle(GuiManager *guiManager) {
    assert(guiManager != NULL);
    guiManager->guiDraw = !guiManager->guiDraw;
    engine.lockCamera = !guiManager->guiDraw;
    GuiManager_optionsReset(guiManager);
    guiManager->options.menu = true;
}

void GuiManager_optionsReset(GuiManager *guiManager)  {
    assert(guiManager != NULL);
    guiManager->options.level = false;
    guiManager->options.menu = false;
    guiManager->options.exit = false;
    guiManager->options.settings = false;
    guiManager->options.developer = false;
}

void GuiManager_draw(GuiManager *guiManager) {
    assert(guiManager != NULL);
    glDisable(GL_LIGHTING);
    GuiManager_update(guiManager);

    if(guiManager->guiDraw) {
       if (guiManager->options.level) {
           GuiManager_levelMenu(guiManager);
       } else if (guiManager->options.settings) {
           GuiManager_settingsMenu(guiManager);
       } else if (guiManager->options.menu && guiManager->inGame) {
           GuiManager_gameMenu(guiManager);
       } else if (guiManager->options.menu && !guiManager->inGame) {
               GuiManager_mainMenu(guiManager);
       /*} else if (guiManager->options.developer) {
           GuiManager_developerMenu(guiManager);*/
       } else if (guiManager->options.exit) {
           engine.running = false;
       }
   }
   //Must be drawn after menu
    if(guiManager->inGame) {
        GuiManager_drawHUD(guiManager);
    }
   glEnable(GL_LIGHTING);
}

void GuiManager_setHeightWidth(GuiManager *guiManager, float divideW, float divideH) {
    assert(guiManager != NULL && divideW != 0 && divideH != 0);
    guiManager->width = (float) guiManager->glfwWidth / divideW;
    guiManager->height = (float) guiManager->glfwHeight / divideH;
}

void GuiManager_setMenuPosition(GuiManager *guiManager, float divideW, float divideH) {
    assert(guiManager != NULL && divideW != 0 && divideH != 0);
    guiManager->xPos = (float) guiManager->glfwWidth / divideW;
    guiManager->yPos = (float) guiManager->glfwHeight / divideH;
}

void GuiManager_startGame(void) {   //TODO: Peter dunno if you need this but its where the game starts
    State *state;
    state = malloc(sizeof (State));
    State_init(state);
    StateManager_push(&engine.sM, state);
    Game_init(state);
}

void GuiManager_stopGame(void) {
    StateManager_top(&engine.sM)->endStateSafely = true;
}

void GuiManager_updateHUD(GuiManager *guiManager, float seconds, int lives, int level) {
    guiManager->hud.updateHUD = true;
    guiManager->hud.nextLives = lives;
    guiManager->hud.nextLevel = level;
    guiManager->hud.nextSeconds = seconds;
}

void GuiManager_drawHUD(GuiManager *guiManager) {
    assert(guiManager != NULL);
    nk_glfw3_new_frame();
    GuiManager_setHeightWidth(guiManager, 2, 18);
    if (guiManager->hud.updateHUD) {
        if (fabs((double) guiManager->hud.prevSeconds - guiManager->hud.nextSeconds) > 0.05) {// Useful when pausing or rendering too fast
            strcpy(guiManager->hud.time, "Time: ");
            sprintf(guiManager->hud.buffer, "%0.2f", guiManager->hud.nextSeconds);
            strcat(guiManager->hud.time, guiManager->hud.buffer);
            guiManager->hud.prevSeconds = guiManager->hud.nextSeconds;
        }

        if (guiManager->hud.prevLives != guiManager->hud.nextLives) {
            strcpy(guiManager->hud.lives, "Lives: ");
            sprintf(guiManager->hud.buffer, "%i", guiManager->hud.nextLives);
            strcat(guiManager->hud.lives, guiManager->hud.buffer);
            guiManager->hud.prevLives = guiManager->hud.nextLives;
        }

        if (guiManager->hud.prevLevel != guiManager->hud.nextLevel ) {
            strcpy(guiManager->hud.levels, "Level: ");
            sprintf(guiManager->hud.buffer, "%i", guiManager->hud.nextLevel );
            strcat(guiManager->hud.levels, guiManager->hud.buffer);
            guiManager->hud.prevLevel = guiManager->hud.nextLevel ;
        }
        guiManager->hud.updateHUD = false;
    }
    if (nk_begin(guiManager->ctx, "", nk_rect(guiManager->glfwWidth/4, 0, guiManager->width, guiManager->height),
                 NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR)) {
        nk_layout_row_dynamic(guiManager->ctx, guiManager->height, 3);
        nk_label(guiManager->ctx, guiManager->hud.time, NK_TEXT_CENTERED);
        nk_label(guiManager->ctx, guiManager->hud.lives, NK_TEXT_CENTERED);
        nk_label(guiManager->ctx, guiManager->hud.levels, NK_TEXT_CENTERED);
    }
    nk_end(guiManager->ctx);
    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

void GuiManager_levelMenu(GuiManager *guiManager) {
    assert(guiManager != NULL);
    nk_glfw3_new_frame();

    GuiManager_setHeightWidth(guiManager, 2, 2.3f);

    /* GUI */
    if (nk_begin(guiManager->ctx, "Big Balls Roll!", nk_rect(guiManager->xPos, guiManager->yPos, guiManager->width, guiManager->height),
                 NK_WINDOW_BORDER|NK_WINDOW_TITLE)) {

        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 11, 1);
        nk_label(guiManager->ctx, "NEW GAME", NK_TEXT_CENTERED);
        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 11, 4);
        if (nk_button_label(guiManager->ctx, "MAIN MENU")) {
            GuiManager_optionsReset(guiManager);
            guiManager->options.menu = true;
        }

        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 4.5f, 1);

        //Name
        if (nk_group_begin(guiManager->ctx, "Name",  NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 11, 3);
            nk_edit_string(guiManager->ctx, NK_EDIT_FIELD | NK_EDIT_GOTO_END_ON_ACTIVATE, engine.playerConfig.name, &engine.playerConfig.nameLength, 256, nk_filter_ascii);

            nk_group_end(guiManager->ctx);
        }

        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 3.1f, 1);
        //Level
        if (nk_group_begin(guiManager->ctx, "Level",  NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 12, 3);
            nk_property_int(guiManager->ctx, "Seed:", INT_MIN, &engine.playerConfig.seed, INT_MAX, 10, 10);

            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 12, 3);
            nk_property_int(guiManager->ctx, "Total levels:", 1, &engine.playerConfig.levels, 20, 1, 10);

            nk_group_end(guiManager->ctx);
        }

        //Confirm button
        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 10, 1);
        if (nk_button_label(guiManager->ctx, "LET EM' ROLL!")) {
            GuiManager_startGame();

            GuiManager_optionsReset(guiManager);
            GuiManager_drawToggle(guiManager);
            guiManager->options.menu = true;
            guiManager->inGame = true;

            //TODO:: Peter, this updates name, seed, levels
        }

    }
    nk_end(guiManager->ctx);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

void GuiManager_settingsMenu(GuiManager *guiManager) {
    assert(guiManager != NULL);
    nk_glfw3_new_frame();

    GuiManager_setHeightWidth(guiManager, 2, 1.35f);

    /* GUI */
    if (nk_begin(guiManager->ctx, "Big Balls Roll!", nk_rect(guiManager->xPos, guiManager->yPos, guiManager->width, guiManager->height),
                 NK_WINDOW_BORDER|NK_WINDOW_TITLE)) {

        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 20, 1);
        nk_label(guiManager->ctx, "SETTINGS", NK_TEXT_CENTERED);
        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 20, 4);
        if (nk_button_label(guiManager->ctx, "MAIN MENU")) {
            GuiManager_optionsReset(guiManager);
            guiManager->options.menu = true;
        }
       /* nk_label(guiManager->ctx, "", NK_TEXT_CENTERED);
        nk_label(guiManager->ctx, "", NK_TEXT_CENTERED);
        if (nk_button_label(guiManager->ctx, "DEVELOPER")) {
            GuiManager_optionsReset(guiManager);
            guiManager->options.developer = true;
        }*/

        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 4.3f, 1);

        //Window settings
        if (nk_group_begin(guiManager->ctx, "Window", NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 21, 3);
            nk_property_int(guiManager->ctx, "Width:", 1280, &engine.playerConfig.width, 3840, 10, 10);
            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 21, 3);
            nk_property_int(guiManager->ctx, "Height:", 720, &engine.playerConfig.height, 2160, 10, 10);
            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 21, 3);
            nk_label(guiManager->ctx, "Windowed mode: ", NK_TEXT_LEFT);

            if (nk_option_label(guiManager->ctx, "Enabled", engine.playerConfig.windowedMode == true)) engine.playerConfig.windowedMode = true;
            if (nk_option_label(guiManager->ctx, "Disabled", engine.playerConfig.windowedMode == false)) engine.playerConfig.windowedMode = false;
            nk_group_end(guiManager->ctx);
        }

        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 5.5f, 1);

        //Audio settings
        if (nk_group_begin(guiManager->ctx, "Audio", NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 20, 3);
            nk_property_int(guiManager->ctx, "Volume:", 0, &engine.playerConfig.volume, 100, 10, 10);
            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 20, 3);
            nk_label(guiManager->ctx, "Sound: ", NK_TEXT_LEFT);
            if (nk_option_label(guiManager->ctx, "Enabled", engine.playerConfig.sound == true)) engine.playerConfig.sound = true;
            if (nk_option_label(guiManager->ctx, "Disabled", engine.playerConfig.sound == false)) engine.playerConfig.sound = false;
            nk_group_end(guiManager->ctx);
        }

        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 3, 1);

        //Mouse settings
        if (nk_group_begin(guiManager->ctx, "Mouse", NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 21, 3);
            nk_label(guiManager->ctx, "Sensitivity: ", NK_TEXT_LEFT);
            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 21, 3);
            nk_property_int(guiManager->ctx, "Vertical:", 0, &engine.playerConfig.verticalSens, 100, 10, 10);
            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 21, 3);
            nk_property_int(guiManager->ctx, "Horizontal:", 0, &engine.playerConfig.horizontalSens, 100, 10, 10);

            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 21, 3);
            nk_label(guiManager->ctx, "Horizontal lock: ", NK_TEXT_LEFT);
            if (nk_option_label(guiManager->ctx, "Enabled", engine.playerConfig.horizontalLock == true)) engine.playerConfig.horizontalLock = true;
            if (nk_option_label(guiManager->ctx, "Disabled", engine.playerConfig.horizontalLock == false)) engine.playerConfig.horizontalLock = false;
            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 21, 1);
            nk_label(guiManager->ctx, "When enabled you must right click to pan the camera.", NK_TEXT_LEFT);
            nk_group_end(guiManager->ctx);
        }

        //Confirm button
        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 20, 1);
        if (nk_button_label(guiManager->ctx, "Confirm")) {
            //TODO:: Peter, this updates volume, sound toggle, V sens, H sens, H Lock toggle and window size
        }
    }
    nk_end(guiManager->ctx);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

/*void GuiManager_developerMenu(GuiManager *guiManager) {
    assert(guiManager != NULL);
    nk_glfw3_new_frame();

    GuiManager_setHeightWidth(guiManager, 2, 3);


    if (nk_begin(guiManager->ctx, "Big Balls Roll!", nk_rect(guiManager->xPos, guiManager->yPos, guiManager->width, guiManager->height),
                 NK_WINDOW_BORDER|NK_WINDOW_TITLE)) {

        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 9, 1);
        nk_label(guiManager->ctx, "DEVELOPER SETTINGS", NK_TEXT_CENTERED);
        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 9, 4);
        if (nk_button_label(guiManager->ctx, "MAIN MENU")) {
            GuiManager_optionsReset(guiManager);
            guiManager->options.menu = true;
        }
        nk_label(guiManager->ctx, "", NK_TEXT_CENTERED);
        nk_label(guiManager->ctx, "", NK_TEXT_CENTERED);
        if (nk_button_label(guiManager->ctx, "SETTINGS")) {
            GuiManager_optionsReset(guiManager);
            guiManager->options.settings = true;
        }

        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 2.5f, 1);

        //Physics settings
        if (nk_group_begin(guiManager->ctx, "Physics", NK_WINDOW_BORDER | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 9, 3);
            nk_property_int(guiManager->ctx, "Gravity:", -100, &guiManager->gravity, 100, 1, 10);
            nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 9, 3);
            nk_label(guiManager->ctx, "Debug Render: ", NK_TEXT_LEFT);
            if (nk_option_label(guiManager->ctx, "Enabled", guiManager->debug == true)) guiManager->debug = true;
            if (nk_option_label(guiManager->ctx, "Disabled", guiManager->debug == false)) guiManager->debug = false;
            nk_group_end(guiManager->ctx);
        }

        //Confirm button
        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 9, 1);
        if (nk_button_label(guiManager->ctx, "Confirm")) {
            //TODO:: pass the stuff
            printf("Gravity: %i\n", guiManager->gravity);
            printf("Debug: %i\n", guiManager->debug);
        }
    }
    nk_end(guiManager->ctx);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}*/

void GuiManager_mainMenu(GuiManager *guiManager) {
    assert(guiManager != NULL);
    nk_glfw3_new_frame();

    GuiManager_setHeightWidth(guiManager, 2, 3);

    /* GUI */
    if (nk_begin(guiManager->ctx, "Big Balls Roll!", nk_rect(guiManager->xPos, guiManager->yPos, guiManager->width, guiManager->height),
                 NK_WINDOW_BORDER|NK_WINDOW_TITLE)) {

        //Menu title
        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 6, 1);
        nk_label(guiManager->ctx, "MAIN MENU", NK_TEXT_CENTERED);

        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 6, 1);
        if (nk_button_label(guiManager->ctx, "NEW GAME")) {
            GuiManager_optionsReset(guiManager);
            guiManager->options.level = true;
        }

        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 6, 1);
        if (nk_button_label(guiManager->ctx, "SETTINGS")) {
            GuiManager_optionsReset(guiManager);
            guiManager->options.settings = true;
        }

        //Exit
        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 6, 1);
        if (nk_button_label(guiManager->ctx, "EXIT")) {
            GuiManager_optionsReset(guiManager);
            guiManager->options.exit = true;
        }
    }
    nk_end(guiManager->ctx);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

void GuiManager_gameMenu(GuiManager *guiManager) {
    assert(guiManager != NULL);
    nk_glfw3_new_frame();

    GuiManager_setHeightWidth(guiManager, 2, 4);

    /* GUI */
    if (nk_begin(guiManager->ctx, "Big Balls Roll!", nk_rect(guiManager->xPos, guiManager->yPos, guiManager->width, guiManager->height),
                 NK_WINDOW_BORDER|NK_WINDOW_TITLE)) {

        //Menu title
        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 5, 1);
        nk_label(guiManager->ctx, "GAME MENU", NK_TEXT_CENTERED);

        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 5, 1);
        if (nk_button_label(guiManager->ctx, "SETTINGS")) {
            GuiManager_optionsReset(guiManager);
            guiManager->options.settings = true;
        }

        //QUIT
        nk_layout_row_dynamic(guiManager->ctx, guiManager->height / 5, 1);
        if (nk_button_label(guiManager->ctx, "QUIT")) {
            GuiManager_stopGame();
            GuiManager_drawToggle(&engine.guiManager);
            GuiManager_optionsReset(guiManager);
            guiManager->options.menu = true;
            guiManager->inGame = false;
        }
    }
    nk_end(guiManager->ctx);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

void GuiManager_mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    nk_glfw3_mouse_button_callback(window, button, action, mods);
}
