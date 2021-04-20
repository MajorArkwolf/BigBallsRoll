#pragma once
#include <stdbool.h>

typedef struct menuOption {
    bool menu, level, settings, exit, developer;
} menuOption;

typedef struct GuiManager {
    struct nk_context *ctx;
    struct nk_font_atlas *atlas;
    menuOption options;
    bool inGame;
    int glfwHeight;
    int glfwWidth;
    float height;
    float width;
    bool guiDraw;
    //TODO: TEMP ADD DEBUG CONFIG OR SOMETHING
    int gravity;
    bool debug;
} GuiManager;

void GuiManager_init(GuiManager *guiManager);

void GuiManager_free(GuiManager *guiManager);

void GuiManager_draw(GuiManager *guiManager);

void GuiManager_optionsReset(GuiManager *guiManager);

void GuiManager_settingsMenu(GuiManager *guiManager);

void GuiManager_gameMenu(GuiManager *guiManager);

void GuiManager_developerMenu(GuiManager *guiManager);

void GuiManager_mainMenu(GuiManager *guiManager);

void GuiManager_levelMenu(GuiManager *guiManager);

void GuiManager_update(GuiManager *guiManager);

void GuiManager_drawToggle(GuiManager *guiManager);

void GuiManager_setHeightWidth(GuiManager *guiManager, float divideW, float divideH);
