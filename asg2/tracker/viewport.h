//
//  viewport.h
//  CPSC-4160-Project-2
//
//  Created by Evan Dorn on 2/23/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#ifndef viewport_h
#define viewport_h

#include "drawable.h"
#include "gamedata.h"

class Viewport {
public:
    static Viewport& getInstance();
    void draw() const;
    void update();
    
    Vector2f getPosition() const { return position; }
    float X() const { return position[0]; }
    void X(float x) { position[0] = x; }
    float Y() const { return position[1]; }
    void Y(float y) { position[1] = y; }
    
    void setObjectToTrack(const Drawable *obj);
    const Drawable* getObjectToTrack() const { return objectToTrack; }
    
private:
    const Gamedata* gdata;
    Vector2f position;
    unsigned viewWidth;
    unsigned viewHeight;
    unsigned worldWidth;
    unsigned worldHeight;
    Uint16 objWidth;
    Uint16 objHeight;
    
    const Drawable *objectToTrack;
    
    Viewport();
    Viewport(const Viewport&);
    Viewport& operator=(const Viewport&);
};

#endif /* viewport_h */
