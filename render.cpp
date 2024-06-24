#include <windows.h>
#include <cstdio>
#define global_variable static
#define internal static 

struct Render_State
{
    int heigth;
    int width;
    void* memory;

    BITMAPINFO bitmap_info;
   
};
Render_State render_state;
typedef int s32;
typedef unsigned int u32;
typedef short s16;
typedef unsigned short u16;
typedef long long s64;
typedef unsigned long long u64;
typedef char s8;
typedef unsigned char u8;
bool running = true;
#define fraction 0.01
void render_background(){
    if (render_state.memory) { // Check if render_state.memory is allocated
            unsigned int* pixel = (unsigned int*)render_state.memory;
            for (int y = 0; y < render_state.heigth; y++) {
                for (int x = 0; x < render_state.width; x++) {
                    *pixel++ = x*y; // Set pixel color
                }
            }
        }
}
void clear_screen(unsigned int colour){
     if (render_state.memory) { // Check if render_state.memory is allocated
            unsigned int* pixel = (unsigned int*)render_state.memory;
            for (int y = 0; y < render_state.heigth; y++) {
                for (int x = 0; x < render_state.width; x++) {
                    *pixel++ = colour; // Set pixel color
                }
            }
        }
}
inline int
clamp(int min,int val,int max){
    if(val<min) return min;
    if(val>max) return max;
    return val;
}
void draw_rect_in_pixels(int x0,int y0 , int x1,int y1, unsigned int colour ){
    x0  = clamp(0,x0,render_state.width);
    x1  = clamp(0,x1,render_state.width);
    y0  = clamp(0,y0,render_state.heigth);
    y1  = clamp(0,y1,render_state.heigth);
    if (render_state.memory) { // Check if render_state.memory is allocated
            for (int y = y0; y < y1; y++) {
                unsigned int* pixel = (unsigned int*)render_state.memory + x0 + y*render_state.width;
                for (int x = x0; x < x1; x++) {
                    *pixel++ = colour; // Set pixel color
                }
            }
        }
}
void draw_rect(float x,float y,float half_size_x,float half_size_y,u32 colour){
    x *= render_state.heigth*fraction;
    y *= render_state.heigth*fraction;
    half_size_x *= render_state.heigth*fraction;
   half_size_y *= render_state.heigth*fraction;

    x += render_state.width/2.f;
    y += render_state.heigth/2.f;

    int x0 = x-half_size_x;
    int x1 = x+half_size_x;
    int y0 = y-half_size_y;
    int y1 = y+half_size_y;
    draw_rect_in_pixels(x0,y0,x1,y1,colour);
}
void draw_number(int number ,float x,float y,float size ,u32 colour){
    float half_size = size*.5f;
    bool for_start = false;
     while(number||!for_start){
        for_start = true;
        int digit = number%10;
        number = number/10;
        printf("digit: %d",digit);
        switch (digit)
        {
        case 1:{
                draw_rect(x+size,y,half_size,2.5f*size,colour);
                
                x-= size*2.f;}break;
        
        case 2:{
                draw_rect(x,y+size*2.f,1.5f*size,half_size,colour);
                draw_rect(x,y,1.5f*size,half_size,colour);
                draw_rect(x,y-size*2.f,1.5f*size,half_size,colour);
                draw_rect(x+size,y+size,half_size,half_size,colour);
                draw_rect(x-size,y-size,half_size,half_size,colour);
                x-= size*4.f;

        } break;
         case 3:{
                draw_rect(x-half_size,y+size*2.f,size,half_size,colour);
                draw_rect(x-half_size,y,size,half_size,colour);
                draw_rect(x-half_size,y-size*2.f,size,half_size,colour);
                draw_rect(x+half_size,y,half_size,2.5f*size,colour);
                x-= size*4.f;
        } break;
         case 4:{
                draw_rect(x+size,y,half_size,2.5f*size,colour);
                draw_rect(x-size,y+size,half_size,1.5f*size,colour);
                draw_rect(x,y,half_size,half_size,colour);
                x-= size*4.f;
        } break;
         case 5:{
                 draw_rect(x,y+size*2.f,1.5f*size,half_size,colour);
                 draw_rect(x,y,1.5f*size,half_size,colour);
                 draw_rect(x,y-size*2.f,1.5f*size,half_size,colour);
                 draw_rect(x-size,y+size,half_size,half_size,colour);
                 draw_rect(x+size,y-size,half_size,half_size,colour);
                x-= size*4.f;
        } break;
         case 6:{
                draw_rect(x+half_size,y+size*2.f,size,half_size,colour);
                draw_rect(x+half_size,y,size,half_size,colour);
                draw_rect(x+half_size,y-size*2.f,size,half_size,colour);
                draw_rect(x-size,y,half_size,2.5f*size,colour);
                draw_rect(x+size,y-size,half_size,half_size,colour);
                x-= size*4.f;
        } break;
         case 7:{
                draw_rect(x+size,y,half_size,2.5f*size,colour);
                draw_rect(x-half_size,y+size*2.f,size,half_size,colour);
                x-= size*4.f;
        } break;
         case 8:{
                draw_rect(x-size,y,half_size,2.5f*size,colour);
                draw_rect(x+size,y,half_size,2.5f*size,colour);
                draw_rect(x,y+size*2.f,half_size,half_size,colour);
                draw_rect(x,y-size*2.f,half_size,half_size,colour);
                draw_rect(x,y,half_size,half_size,colour);
                x-= size*4.f;
        } break;
         case 9:{
                draw_rect(x-half_size,y+size*2.f,size,half_size,colour);
                draw_rect(x-half_size,y,size,half_size,colour);
                draw_rect(x-half_size,y-size*2.f,size,half_size,colour);
                draw_rect(x+size,y,half_size,2.5f*size,colour);
                draw_rect(x-size,y+size,half_size,half_size,colour);
                x-= size*4.f;  
        } break;
        case 0:{
                draw_rect(x-size,y,half_size,2.5f*size,colour);
                draw_rect(x+size,y,half_size,2.5f*size,colour);
                draw_rect(x,y+size*2.f,half_size,half_size,colour);
                draw_rect(x,y-size*2.f,half_size,half_size,colour);
                x-= size*4.f;
        }
        }
     }

}