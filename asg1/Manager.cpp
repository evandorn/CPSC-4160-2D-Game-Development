//
//  Manager.cpp
//  CPSC416-Project1-SDLAnimation
//
//  Created by Evan Dorn on 2/9/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>

#include "Sprite.h"
#include "Manager.h"
#include "GenerateFrames.h"

void Manager::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw( std::string("Unable to initialize SDL: ")+ SDL_GetError());
    }
    atexit(SDL_Quit);
}

Sprite mySprite;            // New sprite object

// Animation or "game" main event loop
void Manager::play() {
    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_DOUBLEBUF);
    if (screen == NULL) {
        throw std::string("Unable to set video mode: ") + SDL_GetError();
    }
    SDL_Surface *desertBackground = mySprite.getImage("images/background.bmp", false);
    SDL_Surface *samus = mySprite.getImage("images/samus.bmp", true);
    SDL_Surface *metroidLogo = mySprite.getImage("images/metroid.bmp", true);
    
    float x = 700; // -samus->w;
    float y = mySprite.START_Y;
    SDL_Event event;
    bool makeVideo = false;
    bool done = false;
    bool freshFrame = false;
    GenerateFrames genFrames(screen);
    
    // Main animation or "game" loop
    while(!done) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) done = true;
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE) done = true;
                if(event.key.keysym.sym == SDLK_F4) {
                    makeVideo = true;
                }
            }
        }
        if((x <= SCREEN_WIDTH - samus->w) && (x >= 0)) {
            freshFrame = mySprite.update(x);
           // std::cout << "value of x: " << x << std::endl;
        }
        else {
            makeVideo = false;
        }
        if(freshFrame) {
            freshFrame = false;
            if (makeVideo) {
                genFrames.makeFrame();
            }
        }
        if(x <= 0) {
            done = true;
            // exit(0);
        }
        mySprite.draw(desertBackground, screen, backgroundX, backgroundY);
        mySprite.draw(metroidLogo, screen, metroidX, metroidY);
        mySprite.draw(samus, screen, x, y);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(desertBackground);
    SDL_FreeSurface(metroidLogo);
    SDL_FreeSurface(samus);
}
