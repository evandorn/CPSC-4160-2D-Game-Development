//
//  Manager.hpp
//  CPSC416-Project1-SDLAnimation
//
//  Created by Evan Dorn on 2/9/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#ifndef Manager_h
#define Manager_h

#include <SDL.h>

#include "Sprite.h"

class Manager {
public:
    Manager():SCREEN_WIDTH(800),SCREEN_HEIGHT(450),metroidX(300),metroidY(125),backgroundX(0.0),backgroundY(0.0) { }
    void play();
    void init();
    
private:
    const unsigned int SCREEN_WIDTH;             //  = 800u;
    const unsigned int SCREEN_HEIGHT;            //  = 450u;
    const float metroidX;                        // = 300;
    const float metroidY;                        // = 125;
    const float backgroundX;                     // 0.0
    const float backgroundY;                     // 0.0
    /*
    Manager(const Manager&);
    Manager& operator=(const Manager&);
    void drawBackground const;
     */
};

#endif /* Manager_hpp */
