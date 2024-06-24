#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D  0x44
#define VK_E  0x45
#define VK_F  0x46
#define VK_G  0x47
#define VK_H  0x48
#define VK_I  0x49
#define VK_J  0x4A
#define VK_K  0x4B
#define VK_L  0x4C
#define VK_M  0x4D
#define VK_N  0x4E
#define VK_O  0x4F
#define VK_P  0x50
#define VK_Q  0x51
#define VK_R  0x52
#define VK_S  0x53
#define VK_T  0x54
#define VK_U  0x55
#define VK_V  0x56
#define VK_W  0x57
#define VK_X  0x58
#define VK_Y  0x59
#define VK_Z  0x5A
struct Button_State
{
    bool is_down;
    bool changed;
};

enum{
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

struct Input
{
    Button_State buttons[BUTTON_COUNT];
};
Input input = {};