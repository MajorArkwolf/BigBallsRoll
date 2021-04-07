#include "guiManager.h"

#define NK_INCLUDE_DEFAULT_ALLOCATOR


void guiManager_init(GuiContainer *guiContainer) {
    //init font first
    if (nk_init_default(&guiContainer->ctx, &guiContainer->font)) {

    }
}
void guiManager_free(GuiContainer *guiContainer) {

}

void guiManager_input(GuiContainer *guiContainer) {

}

void guiManager_draw(GuiContainer *guiContainer) {

}

void guiManager_window(GuiContainer *guiContainer) {

}

void guiManager_layout(GuiContainer *guiContainer) {

}
