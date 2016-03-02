//
//  world.h
//  CPSC-4160-Project-2
//
//  Created by Evan Dorn on 2/23/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#ifndef world_h
#define world_h

#include <string>

#include "ioManager.h"
#include "frame.h"
#include "viewport.h"

class World {
public:
    World(const std::string& name, int fact);
    // ~World() { ; } // The frame will be deleted by the FrameFactory
    void update();
    void draw() const;
private:
    const IOManager* io;
    Frame* const frame;
    int factor;
    unsigned frameWidth;
    unsigned worldWidth;
    float viewX;
    float viewY;
    const Viewport & view;
    World(const World&);
    World& operator=(const World&);
};

#endif /* world_h */
