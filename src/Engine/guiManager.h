#pragma once
#include <stdbool.h>
typedef struct GLFWwindow GLFWwindow;

#define GUI_BUFFER_SIZE 256

typedef struct menuOption {
    bool menu, level, settings, exit;
} menuOption;

typedef  struct GameOver {
    char buffer[GUI_BUFFER_SIZE];
    char seed[GUI_BUFFER_SIZE];
    char message[GUI_BUFFER_SIZE];
    char name[GUI_BUFFER_SIZE];
    char time[GUI_BUFFER_SIZE];
    char lives[GUI_BUFFER_SIZE];
    char levels[GUI_BUFFER_SIZE];
} GameOver;

typedef struct Hud {
    char buffer[GUI_BUFFER_SIZE];
    char time[GUI_BUFFER_SIZE];
    char lives[GUI_BUFFER_SIZE];
    char levels[GUI_BUFFER_SIZE];
    int nextLives;
    int nextLevel;
    float nextSeconds;
    int prevLives;
    int prevLevel;
    float prevSeconds;
    bool updateHUD;
} Hud;

typedef struct GuiManager {
    struct nk_context *ctx;
    struct nk_font_atlas *atlas;
    menuOption options;
    Hud hud;
    GameOver gameOver;
    bool inGame;
    bool isGameOver;
    int glfwHeight;
    int glfwWidth;
    float height;
    float width;
    float xPos;
    float yPos;
    bool guiDraw;
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
 * Draws hud if in game, regardless of menu state.
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
 * Sets the camera lock to equal inGame or
 * locks the camera if in game and gui is being drawn.
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
 * Updates and sets the screen space position for the menu. Currently set in the middle.
 * @param guiManager The guiManager to update.
 */
void GuiManager_setMenuPosition(GuiManager *guiManager, float divideW, float divideH);

/**
 * Starts the game by setting the state and pushes it onto the stateManager stack.
 */
void GuiManager_startGame(void);

/**
 * Stops the game by setting the state manager to end safely.
 */
void GuiManager_stopGame(void);

/**
 * Displays two buttons at the exit screen of the game, an exit confirmation.
 * @param guiManager The guiManager to update.
 */
void GuiManager_exitMenu(GuiManager *guiManager);

/**
 * Draws the in game hud menu.
 * @param guiManager the gui manager to draw from
 */
void GuiManager_drawHUD(GuiManager *guiManager);

/**
 * Function to update the hud values and to let the GUI manager know when to update the hud next.
 * @param guiManager the gui manager to draw from
 * @param seconds how many seconds to put on the board
 * @param lives remaining lives
 * @param level the current level on
 */
void GuiManager_updateHUD(GuiManager *guiManager, float seconds, int lives, int level);

/**
 * Closes all inactive windows.
 * @param guiManager the guiManager with the windows to close.
 */
void GuiManager_closeInactiveWindows(GuiManager *guiManager);

/**
 * initialises the game over data and sets isGameOver to false which triggers the draw call.
 * A message can be passed and displayed at the top of the screen, i.e. you won, or you lost, etc.
 * @param guiManager with the data to init
 * @param message to display to the player
 * @param level the levels the player completed
 */
void GuiManager_initGameOver(GuiManager *guiManager, const char *message, int level, int lives);

/**
 * Menu that displays the game over screen. GuiManager_initGameOver prepares the data that is displayed
 * on this screen.
 * @param guiManager with the ctx to draw to
 */
void GuiManager_gameOver(GuiManager *guiManager);
