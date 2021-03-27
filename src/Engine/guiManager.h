#pragma once
#include "GUI.h"

typedef struct GuiContainer { //TODO: find out what else I need
    struct nk_context ctx; //TODO: decide if we need an array
    struct nk_user_font font; //TODO: probably can remove
} GuiContainer;

void guiManager_init(GuiContainer *guiContainer);

void guiManager_free(GuiContainer *guiContainer);

void guiManager_input(GuiContainer *guiContainer);

void guiManager_draw(GuiContainer *guiContainer);

void guiManager_window(GuiContainer *guiContainer);

void guiManager_layout(GuiContainer *guiContainer);
