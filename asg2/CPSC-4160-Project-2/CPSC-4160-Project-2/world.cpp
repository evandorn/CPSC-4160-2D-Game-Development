//
//  world.cpp
//  CPSC-4160-Project-2
//
//  Created by Evan Dorn on 2/23/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#include <iostream>

#include "world.h"
#include "frameFactory.h"

World::World(const std::string& name, int fact) :
io( IOManager::getInstance() ),
frame( FrameFactory::getInstance()->getFrame(name) ),
factor(fact),
frameWidth( frame->getWidth() ),
worldWidth( WORLD_WIDTH ),
viewX(0.0), viewY(0.0),
view(Viewport::getInstance())
{}

void World::update() {
    viewX = static_cast<int>(view.X() / factor) % frameWidth;
    viewY = view.Y();
}

void World::draw() const {
    frame->draw(viewX, viewY, 0, 0);
    frame->draw(0, viewY, frameWidth-viewX, 0);
}
