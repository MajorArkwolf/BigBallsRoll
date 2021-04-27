#pragma once
#include <stdbool.h>
typedef struct GLFWwindow GLFWwindow;

typedef struct menuOption {
    bool menu, level, settings, exit, developer;
} menuOption;

typedef struct Hud {
    char buffer[256];
    char time[256];
    char lives[256];
    char levels[256];
    int prevLives;
    int prevLevel;
    float prevSeconds;
} Hud;

typedef struct GuiManager {
    struct nk_context *ctx;
    struct nk_context *hudCtx;
    struct nk_font_atlas *atlas;
    menuOption options;
    Hud hud;
    bool inGame;
    int glfwHeight;
    int glfwWidth;
    float height;
    float width;
    float xPos;
    float yPos;
    bool guiDraw;
    bool processInput;
    //TODO: TEMP ADD DEBUG CONFIG OR SOMETHING
    int gravity;
    bool debug;
} GuiManager;

/**
 * Initializes a guiManager using nuklear_glfw for the ctx and atlas.
 * Sets all other values to defaults that aren't all 0 or null.
 * @param guiManager The guiManager to init
 */
void GuiManager_init(GuiManager *guiManager);

/**
 * Frees a ctx and atlas using nk_glfw3_shutdown()
 * @param guiManager The gui manager to free
 */
void GuiManager_free(GuiManager *guiManager);

/**
 * Draws one menu to the screen. Will check which menu should be drawn currently.
 * Does not check guiDraw itself as this should be checked externally to reduce stack setup/teardown.
 * @param guiManager The guiManager to draw
 */
void GuiManager_draw(GuiManager *guiManager);

/**
 * Resets all menu options to false.
 * @param guiManager The guiManager to reset.
 */
void GuiManager_optionsReset(GuiManager *guiManager);

/**
 * When called displays the settings menu for one frame.
 * @param guiManager The guiManager to draw to.
 */
void GuiManager_settingsMenu(GuiManager *guiManager);

/**
 * When called displays the game menu for one frame.
 * @param guiManager The guiManager to draw to.
 */
void GuiManager_gameMenu(GuiManager *guiManager);

/**
 * When called displays the developer menu for one frame.
 * @param guiManager The guiManager to draw to.
 */
void GuiManager_developerMenu(GuiManager *guiManager);

/**
 * When called displays the main menu for one frame.
 * @param guiManager The guiManager to draw to.
 */
void GuiManager_mainMenu(GuiManager *guiManager);

/**
 * When called displays the level menu for one frame.
 * @param guiManager The guiManager to draw to.
 */
void GuiManager_levelMenu(GuiManager *guiManager);

/**
 * Updates the glfwWidth and glfwHeight before drawing so that UI can be scaled
 * if the window has been resized.
 * @param guiManager The guiManager to update.
 */
void GuiManager_update(GuiManager *guiManager);

/**
 * Toggles guiDraw on or off.
 * @param guiManager The guiManager to toggle
 */
void GuiManager_drawToggle(GuiManager *guiManager);

/**
 * Sets the height and width of the GUI window to be drawn. Divides glfwHeight by divideH
 * and glfwWidth by divideW.
 * @param guiManager The guiManager we want to draw to
 * @param divideW The width to divide by
 * @param divideH The height to divide by
 */
void GuiManager_setHeightWidth(GuiManager *guiManager, float divideW, float divideH);

/**
 * Interface to pass events to Nuklear for the GUI
 * @param window the current window activating the event.
 * @param button the button id that caused the event to occur.
 * @param action the action of the event such as button down.
 * @param mods the modifiers
 */
void GuiManager_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

/**
 * Updates and sets the screen position for the menu. Currently set in the middle.
 * @param guiManager The guiManager to update.
 */
void GuiManager_setMenuPosition(GuiManager *guiManager, float divideW, float divideH);

/**
 * Sets the state and pushes it onto the stateManager stack.
 */
void GuiManager_startGame(void);

/**
 * Pops the state from the stateManager stack.
 */
void GuiManager_stopGame(void);

void GuiManager_hud(GuiManager *guiManager, float seconds, int lives, int level);
