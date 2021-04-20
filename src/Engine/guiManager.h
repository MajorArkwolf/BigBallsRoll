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
    int height;
    int width;
    int gravity;
    bool debug;
} GuiManager;

void GuiManager_init(void);

void GuiManager_free(void);

void GuiManager_draw(void);

void GuiManager_optionsReset(void);

void GuiManager_settingsMenu(void);

void GuiManager_gameMenu(void);

void GuiManager_developerMenu(void);

void GuiManager_mainMenu(void);

void GuiManager_levelMenu(void);

void GuiManager_update(void);
