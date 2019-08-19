#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define W 400
#define H 1000

#define LINE W/2

#define CAR_W 25
#define CAR_H 50

#define PI 3.14

#define PID_L 100

#define P_K 1.0f
#define D_K 1.0f
#define I_K 5.0f

float pid_data[PID_L];

SDL_Window* window;
SDL_Renderer* renderer;
int quit = 0;

int init(char* title, int w, int h) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        return 0;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    return 1;
}

typedef struct car {
    float xpos;
    float ypos;
    float rotation;
}car;

void move_car(car* c, float speed) {
    c->xpos += (cosf(c->rotation)*speed);
    c->ypos += (sinf(c->rotation)*speed);
}

void draw_car(car c) {
    float lt_x = (-CAR_W/2) * cosf(c.rotation) - (CAR_H/2) * sinf(c.rotation);
    float lt_y = (CAR_H/2) * cosf(c.rotation) + (-CAR_W/2) * sinf(c.rotation);

    float rt_x = (CAR_W/2) * cosf(c.rotation) - (CAR_H/2) * sinf(c.rotation);
    float rt_y = (CAR_H/2) * cosf(c.rotation) + (CAR_W/2) * sinf(c.rotation);

    float lb_x = (-CAR_W/2) * cosf(c.rotation) - (-CAR_H/2) * sinf(c.rotation);
    float lb_y = (-CAR_H/2) * cosf(c.rotation) + (-CAR_W/2) * sinf(c.rotation);

    float rb_x = (CAR_W/2) * cosf(c.rotation) - (-CAR_H/2) * sinf(c.rotation);
    float rb_y = (-CAR_H/2) * cosf(c.rotation) + (CAR_W/2) * sinf(c.rotation);




    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderDrawLineF(renderer, lt_x + c.xpos, lt_y + c.ypos,
                        rt_x + c.xpos, rt_y + c.ypos);


    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderDrawLineF(renderer, lb_x + c.xpos, lb_y + c.ypos,
                        rb_x + c.xpos, rb_y + c.ypos);



    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderDrawLineF(renderer, lb_x + c.xpos, lb_y + c.ypos,
                        lt_x + c.xpos, lt_y + c.ypos);


    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
    SDL_RenderDrawLineF(renderer, rb_x + c.xpos, rb_y + c.ypos,
                        rt_x + c.xpos, rt_y + c.ypos);

    //SDL_RenderDrawLineF(renderer, rb_x + c.xpos, rb_y + c.ypos,
    //0.0f, 0.0f);

}

// ta errado, ta tudo errado
float cross(car c) {
    float cross = 0.0f;

    float rt_x = (CAR_W/2) * cosf(c.rotation) - (CAR_H/2) * sinf(c.rotation);
    float rb_x = (CAR_W/2) * cosf(c.rotation) - (-CAR_H/2) * sinf(c.rotation);

    cross = (rt_x+rb_x)/2;
    cross += c.xpos;
    cross -= LINE;

    return cross;
}

float p_pid_car(car c) {
    return cross(c);
}

float d_pid_car(car c) {

    if(pid_data[0] == 0.0f) return 0.0f;

    return p_pid_car(c)/(pid_data[0]);
}

float i_pid_car(car c) {
    float ans = 0.0f;

    for(int i = 0; i < PID_L; i++) {
        ans += pid_data[i];
    }

    return ans/(float)PID_L;
}

void pid_update(car c) {
    for(int i = 1; i < PID_L; i++) {
        pid_data[i] = pid_data[i-1];
    }

    pid_data[0] = cross(c);
}

float pid_car(car c) {
    float ans = 0.0f;

    ans += p_pid_car(c) * P_K;
    ans += d_pid_car(c) * D_K;
    ans += i_pid_car(c) * I_K;

    //printf("%0.5f\n", i_pid_car(c) * I_K);

    pid_update(c);

    return ans;
}

void update_car(car* c) {

    float err = pid_car(*c);

    if((err*err) > 500.0f) {
        if(err > 0.0f) {
            c->rotation -= 0.1f;
        } else {
            c->rotation += 0.1f;
        }
    } else {
        move_car(c, 0.005f);
    }
}

int main() {

    for(int i = 0; i < PID_L; i++) pid_data[i] = 0.0f;

    init("Rob sim", W, H);

    car c = {.xpos = W/2+5, .ypos = H - 100, .rotation = -PI/2 - 0.5};

    while(!quit) {
        SDL_Event e;

        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT)
                quit = 1;

            if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = 1; break;

                case SDLK_LEFT:
                    c.rotation -= 0.4f; break;
                case SDLK_RIGHT:
                    c.rotation += 0.4f; break;

                default: break;
                }
            }
        }

        //c.rotation += 0.001f;
        update_car(&c);
        //move_car(&c, 0.04f);

        SDL_SetRenderDrawColor(renderer, 0xaa, 0xaa, 0xaa, 0xff);
        SDL_RenderClear(renderer);


        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderDrawLine(renderer, LINE, 0, LINE, H);

        draw_car(c);
        cross(c);

        SDL_RenderPresent(renderer);

    }

    return 0;
}
