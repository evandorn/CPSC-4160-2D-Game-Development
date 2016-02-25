//
//  Sprite.cpp
//  CPSC-4160-Project1
//
//  Created by Evan Dorn on 1/28/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#include "Sprite.h"

SDL_Surface* Sprite::getImage(const std::string& filename, bool setColorKey) {
    SDL_Surface *temp = SDL_LoadBMP(filename.c_str());
    if (temp == NULL) {
        throw std::string("Unable to load bitmap.")+SDL_GetError();
    }
    if (setColorKey) {
        Uint32 colorkey = SDL_MapRGB(temp->format, 255, 0, 255);
        SDL_SetColorKey(temp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
    }
    SDL_Surface *image = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    return image;
}

void Sprite::draw(SDL_Surface* image, SDL_Surface* screen,
          float x = 0.0, float y = 0.0) {
    Uint16 w = image->w;
    Uint16 h = image->h;
    Sint16 xCoord = static_cast<Sint16>(x);
    Sint16 yCoord = static_cast<Sint16>(y);
    SDL_Rect src = { 0, 0, w, h };
    SDL_Rect dest = { xCoord, yCoord, 0, 0 };
    SDL_BlitSurface(image, &src, screen, &dest);
}

bool Sprite::update(float& x) {
    static unsigned int remainder = 0u;
    static unsigned int currentTicks = 0u;
    static unsigned int prevTicks = SDL_GetTicks();
    currentTicks = SDL_GetTicks();
    unsigned int elapsedTicks = currentTicks - prevTicks + remainder;
    
    if(elapsedTicks < DT) return false;
    
    // float incr = X_VELOCITY * DT * 0.001;
    
    float decrement = X_VELOCITY * DT * 0.001;
    x = x - decrement;
    
    // x += incr;
    
    prevTicks = currentTicks;
    remainder = elapsedTicks - DT;
    
    return true;
}
