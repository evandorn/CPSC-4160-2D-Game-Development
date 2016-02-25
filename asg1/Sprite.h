//
//  Sprite.h
//  CPSC-4160-Project1
//
//  Created by Evan Dorn on 1/29/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#ifndef Sprite_h
#define Sprite_h

#include <SDL.h>
#include <iostream>

class Sprite {
public:
    Sprite() : START_Y(325.0), X_VELOCITY(100.0), DT(17) { }   // constructor
    void draw(SDL_Surface* image, SDL_Surface* screen,
              float x, float y);
    SDL_Surface* getImage(const std::string& filename, bool setColorKey);
    bool update(float& x);
    friend class Manager;
private:
    const float START_Y;                    // = 325;
    const float X_VELOCITY;                 // = 100.0;
    // Approximately 60 frames per second: 60/1000
    const unsigned int DT;                  // = 17u;
};

#endif /* Sprite_h */
