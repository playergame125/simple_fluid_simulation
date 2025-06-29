#include <iostream>
#include <SDL3/SDL.h>
#include <string>




#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512
#define SCALE_X 1
#define SCALE_Y 1
#define numparticles 500
#define FPS_CAP 80

SDL_Event GlobalEvent;
auto* keystates=SDL_GetKeyboardState(NULL);
//only initialization stuff
bool initWindow(SDL_Window** window);
bool initRenderer(SDL_Renderer** renderer,SDL_Window** window);

//this is used to check if specified event type happened
void hasQuit(bool* check){
    while(SDL_PollEvent(&GlobalEvent)){
        if(GlobalEvent.type== SDL_EVENT_QUIT){
        *check =false;
    }
    if (GlobalEvent.type == SDL_EVENT_KEY_DOWN) {
            // SDL3 uses event.key.keysym.scancode
            if (GlobalEvent.key.scancode == SDL_SCANCODE_ESCAPE) {
                *check = false;
            }
        }
    }

}
void initall(SDL_Window** window,SDL_Renderer** renderer){
    if(!initWindow(window)){
        std::cout<<"\n failde to initi window";
    }
    if(!initRenderer(renderer,window)){
        std::cout<<"\n failde to initi renderer";
    } 
}

bool initWindow(SDL_Window** window){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("FLUID SIMULATION", WINDOW_WIDTH, WINDOW_HEIGHT,SDL_WINDOW_RESIZABLE);
    if (!*window) {
        SDL_Log("Could not create window: %s", SDL_GetError());
        return false;
    }
    return true;
}

bool initRenderer(SDL_Renderer** renderer,SDL_Window** window){
    *renderer = SDL_CreateRenderer(*window,NULL);
    if(!*renderer){
        return false;
    }
    return true;
}

//---------------------------------------------------------------------------------------------
//parte di update
void update(){

}
//-----------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//parte di render
void render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}
//-----------------------------------------------------------------------------------------------

int main(int argc, char* argv[]){
    (void)argc;
    (void)argv;

    SDL_Window* window=NULL;
    SDL_Renderer* renderer=NULL;
    initall(&window,&renderer);




    //variable for fps cap
    bool running = true;
    Uint64 now = SDL_GetTicks();
    Uint64 last = now;
    float deltaTime = 0;
    const Uint32 frameDelay = 1000 / FPS_CAP;

    // ✅ Add these:
    int frameCount = 0;
    float fps = 0.0f;
    Uint64 fpsTimer = SDL_GetTicks();
    std::cout << "Type of keystates: " << typeid(keystates).name() << std::endl;

    while(running){
        last = now;
        now = SDL_GetTicks();
        deltaTime = (now - last) / 1000.0f;

        frameCount++;  // ✅ Count frames

        if (now - fpsTimer >= 1000) { // 1 second passed
            fps = frameCount * 1000.0f / (now - fpsTimer);
            std::cout << "FPS: " << (int)fps << std::endl;

            fpsTimer = now;
            frameCount = 0;
        }
        hasQuit(&running);
        update();
        render(renderer);






        // apply fps cap
        Uint32 frameTime = SDL_GetTicks() - now;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }


        
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}