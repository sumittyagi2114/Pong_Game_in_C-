#include <windows.h>
#include <cstdio> // Added for debugging output
#include"render.cpp"
#include"platform_comman.cpp"

#define is_down(b) input.buttons[b].is_down
#define pressed(b) (input.buttons[b].is_down && input.buttons[b].changed)
#define released(b) (!input.buttons[b].is_down && input.buttons[b].changed)

float player_x = 0.f;
float player_y = 0.f;
float ball_x =  0.f;
float ball_y =  0.f;
float dt = 0.016666f;
float ball_x_speed = 13.f;
float ball_y_speed = 0.f;
int player_1_score=0;
int player_2_score =0;
float acc_ai = 0.f;
LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;
    switch (uMsg) {
        case WM_CLOSE:
        case WM_DESTROY: {
            running = false;
        } break;

        case WM_SIZE: {
            RECT rect;
            GetClientRect(hwnd, &rect);
            render_state.width = rect.right - rect.left; // Use global render_state.width
            render_state.heigth = rect.bottom - rect.top; // Use global render_state.height
            int size = render_state.width * render_state.heigth * sizeof(unsigned int);
            if (render_state.memory) {
                VirtualFree(render_state.memory, 0, MEM_RELEASE); // Free existing render_state.memory if allocated
            }
            render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
            render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
            render_state.bitmap_info.bmiHeader.biHeight = render_state.heigth; // Negative for top-down DIB
            render_state.bitmap_info.bmiHeader.biPlanes = 1;
            render_state.bitmap_info.bmiHeader.biBitCount = 32;
            render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;
            printf("Buffer size: %d, Width: %d, Height: %d\n", size, render_state.width, render_state.heigth); // Debug output
        } break;
        
       
        
        default: {
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
    return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Window class
    WNDCLASS window_class = {};
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpszClassName = "Game window class";
    window_class.lpfnWndProc = window_callback;

    // Register class
    RegisterClass(&window_class);

    // Create window
    HWND window = CreateWindow(window_class.lpszClassName, "MY FIRST GAME!",
                               WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                               CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
                               0, 0, hInstance, 0);

    HDC hdc = GetDC(window);
    LARGE_INTEGER frame_begin_time;
    QueryPerformanceCounter(&frame_begin_time);

    float performance_frequency;
{
    LARGE_INTEGER perf;
    QueryPerformanceCounter(&perf);
    performance_frequency = (float)(perf.QuadPart);
}
    while (running) {
        // Input
        MSG message;
        for(int i=0;i<BUTTON_COUNT;i++){
            input.buttons->changed = false;
        }
        while (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) { // Change PeekMessage parameters to process all messages
            switch (message.message)
            {
                case WM_KEYUP:
                case WM_KEYDOWN:{
                    u32 vk_code = (u32)message.wParam;
                    bool isdown = ((message.lParam & (1<<31))==0);
                    
#define process_button(b,vk)  \
case vk:{\
input.buttons[b].is_down = isdown;\
input.buttons[b].changed = true; \
}break;                
                    switch (vk_code)
                    {
                        process_button(BUTTON_W,VK_W);
                        process_button(BUTTON_S,VK_S);
                        process_button(BUTTON_D,VK_D);
                        process_button(BUTTON_A,VK_A);
                        process_button(BUTTON_UP,VK_UP);
                        process_button(BUTTON_DOWN,VK_DOWN);
                        process_button(BUTTON_LEFT,VK_LEFT);
                        process_button(BUTTON_RIGHT,VK_RIGHT);
                        
                        break;
                    
                    default:
                        break;
                    }

                } break;

                default: {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }break;
            }
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        float player_1_half_x = 2.5;
        float player_1_half_y = 12;
        float player_2_half_x = 2.5;
        float player_2_half_y = 12;
        float arena_half_x = 85 ;
        float arena_half_y = 45 ;
        float speed_x = 0.f;
        float speed_y = 0.f;
        float acc = 5.f; 
        // Simulate
        float ball_half = 1.f;
       clear_screen(0xff5500);
       draw_rect(0,0,arena_half_x,arena_half_y,0xffaa33);
        if (pressed(BUTTON_W)) speed_y += acc;
        if (pressed(BUTTON_S))  speed_y -= acc;
      //  if (pressed(BUTTON_UP)) speed_x += acc;
       // if (pressed(BUTTON_DOWN)) speed_x -= acc;
        acc_ai = (ball_y - player_x)*.7f;
        if(acc_ai>1300) acc_ai = 1300;
        if(acc_ai<-1300) acc_ai = -1300;
        speed_x +=acc_ai;
        player_y += speed_y*dt;
        player_x += speed_x*dt;
        if(player_y + player_1_half_y > arena_half_y){
            player_y = arena_half_y - player_1_half_y;
            speed_y = 0;
        }
        else  if(player_y - player_1_half_y < -1*arena_half_y){
            player_y = -1*arena_half_y + player_1_half_y;
            speed_y = 0;
        }
        if(player_x + player_2_half_y > arena_half_y){
            player_x = arena_half_y - player_2_half_y;
            speed_x = 0;
        }
        else  if(player_x - player_2_half_y < -1*arena_half_y){
            player_x = -1*arena_half_y + player_2_half_y;
            speed_x = 0;
        }
        ball_x += ball_x_speed*dt;
        ball_y += ball_y_speed*dt; 
    if ((ball_x + ball_half > 80 - player_1_half_x) && 
    (ball_x - ball_half < 80 - player_1_half_x) && 
    (ball_y + ball_half > player_x - player_1_half_y) && 
    (ball_y + ball_half < player_x + player_1_half_y)) {
        ball_x = 80 - player_1_half_x - ball_half;
        ball_x_speed *= -1;
        ball_y_speed = (ball_y-player_x) ;
}
     if ((ball_x + ball_half > -80 - player_2_half_x) && 
    (ball_x - ball_half < -80 - player_2_half_x) && 
    (ball_y + ball_half > player_y - player_2_half_y) && 
   (ball_y + ball_half < player_y + player_2_half_y)) {
        ball_x = -80 + player_2_half_x + ball_half;
        ball_x_speed *= -1;
        ball_y_speed = (ball_y-player_y) ;
}
    if(ball_y + ball_half > arena_half_y){
           ball_y = arena_half_y - ball_half;
            ball_y_speed *= -1;
    }
     else  if(ball_y - ball_half < -arena_half_y){
           ball_y = -arena_half_y + ball_half;
           ball_y_speed *= -1;
     }
        if(ball_x + ball_half > arena_half_x){
            ball_x_speed *=-1;
            ball_y_speed =0;
            ball_x =0;
            ball_y=0;
            player_1_score++;
        }
         else if(ball_x - ball_half < -arena_half_x){
            ball_x_speed *=-1;
            ball_y_speed =0;
            ball_x =0;
            ball_y=0;
            player_2_score++;
        }
        printf("player: %d\n", player_1_score);
        printf("player: %d\n", player_2_score);
        draw_number(player_1_score,-10,40,1.f,0xbbffbb);
        draw_number(player_2_score,10,40,1.f,0xbbffbb);
        draw_rect(ball_x,ball_y,ball_half,ball_half,0x00ff22);
        draw_rect(80,player_x,player_1_half_x,player_1_half_y,0xff0000);
        draw_rect(-80,player_y,player_2_half_x,player_2_half_y,0xff0000);
           
        
        StretchDIBits(hdc, 0, 0, render_state.width, render_state.heigth, 0, 0, render_state.width, render_state.heigth,
                      render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }

    ReleaseDC(window, hdc); // Ensure HDC is released
    LARGE_INTEGER frame_end_time;
    QueryPerformanceCounter(&frame_end_time);
    dt = (float)(frame_end_time.QuadPart-frame_begin_time.QuadPart)/performance_frequency;
    frame_begin_time = frame_end_time;

}