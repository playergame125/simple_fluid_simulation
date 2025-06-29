#include <iostream>
#include <SDL3/SDL.h>

struct particles
{
    int posX;
    int posY;
    int color[3]={255,255,255};
    float force[2]{0,0};//x,y
    float speed=1;
    particles(int x,int y){};
    void move(){};
    //this function is called when i need to subtract/add force vector
    void changeforce(int x,int y){};


};
