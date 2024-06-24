
**********************************************************
******************* Simple Pong Game *********************
**********************************************************

********************** Author: Sumit Tyagi *****************

==========================================================
||                   Overview                           ||
==========================================================

This project is a simple Pong game implemented in C++ using the Windows API 
for handling window creation, input, and rendering. The game features two 
players, each controlling a paddle, and a ball that bounces off the paddles 
and the arena boundaries. The goal is to score points by getting the ball 
past the opponent's paddle.

==========================================================
||                   Features                           ||
==========================================================

- Two-player control using keyboard inputs.
- Ball physics including bouncing off paddles and arena boundaries.
- Simple AI for controlling the second paddle.
- Score tracking for both players.
- Rendering using `StretchDIBits`.

==========================================================
||                   Files                              ||
==========================================================

- `main.cpp`: The main game loop and window handling.
- `render.cpp`: Rendering functions.
- `platform_common.cpp`: Platform-specific functions for handling input states.

==========================================================
||                   Controls                           ||
==========================================================

- Player 1:
  - Move Up: `W`
  - Move Down: `S`
- Player 2:
  - Move Up: `Arrow Up`
  - Move Down: `Arrow Down`

==========================================================
||                   Code Explanation                   ||
==========================================================

----------------------------------------------------------
--                   main.cpp                           --
----------------------------------------------------------

1. **Global Variables**:
   - Variables for player positions, ball position, speeds, scores, and AI acceleration.

2. **Window Callback Function**:
   - Handles window messages such as `WM_CLOSE`, `WM_DESTROY`, and `WM_SIZE` to manage 
     the game state and rendering buffer.

3. **WinMain Function**: 
   - Sets up the window class and creates the game window.
   - Handles the main game loop including input processing, simulation, and rendering.
   - Uses `PeekMessage` to process keyboard input and update game state accordingly.

4. **Input Handling**: 
   - Uses macros `is_down`, `pressed`, and `released` to manage button states.
   - Processes keyboard events to update button states.

5. **Game Logic**: 
   - Updates player positions based on input.
   - Updates ball position and checks for collisions with paddles and arena boundaries.
   - Handles scoring when the ball passes a paddle.

6. **Rendering**: 
   - Clears the screen and draws the arena, paddles, ball, and scores.
   - Uses `StretchDIBits` to render the game frame to the window.

----------------------------------------------------------
--               platform_common.cpp                    --
----------------------------------------------------------

The `platform_common.cpp` file defines key codes for input handling and structures 
to manage button states.

### Key Codes
Defines key codes for letters A to Z:
```
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A
```

### Button State Structure
Defines a structure to manage the state of buttons:
```
struct Button_State {
    bool is_down;
    bool changed;
};
```

### Button Enumeration
Enumerates the buttons used in the game:
```
enum {
    BUTTON_UP,
    BUTTON_W,
    BUTTON_A,
    BUTTON_S,
    BUTTON_D,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_B,
    BUTTON_C,
    BUTTON_E,
    BUTTON_F,
    BUTTON_G,
    BUTTON_H,
    BUTTON_I,
    BUTTON_J,
    BUTTON_K,
    BUTTON_L,
    BUTTON_M,
    BUTTON_N,
    BUTTON_O,
    BUTTON_P,
    BUTTON_Q,
    BUTTON_R,
    BUTTON_T,
    BUTTON_U,
    BUTTON_V,
    BUTTON_X,
    BUTTON_Y,
    BUTTON_Z,
    BUTTON_COUNT,
};
```

### Input Structure
Defines an input structure containing an array of button states:
```
struct Input {
    Button_State buttons[BUTTON_COUNT];
};
Input input = {};
```

----------------------------------------------------------
--                   render.cpp                         --
----------------------------------------------------------

The `render.cpp` file contains functions for rendering the game.

### Render State Structure
Defines a structure to manage the rendering state:
```
struct Render_State {
    int height;
    int width;
    void* memory;
    BITMAPINFO bitmap_info;
};
Render_State render_state;
```

### Rendering Functions

1. **render_background()**:
   - Fills the background with a gradient pattern.

2. **clear_screen(unsigned int colour)**:
   - Fills the screen with a solid color.

3. **clamp(int min, int val, int max)**:
   - Clamps a value between a minimum and maximum.

4. **draw_rect_in_pixels(int x0, int y0, int x1, int y1, unsigned int colour)**:
   - Draws a rectangle in pixel coordinates.

5. **draw_rect(float x, float y, float half_size_x, float half_size_y, u32 colour)**:
   - Draws a rectangle with a specified color.

6. **draw_number(int number, float x, float y, float size, u32 colour)**:
   - Draws a number at the specified position and size.

==========================================================
||                   How to Run                         ||
==========================================================

1. Ensure you have a C++ compiler and the Windows SDK installed.
2. Compile the code along with `render.cpp` and `platform_common.cpp`.
3. Run the resulting executable to start the game.

**********************************************************
******************* Have Fun Playing! ********************
**********************************************************
