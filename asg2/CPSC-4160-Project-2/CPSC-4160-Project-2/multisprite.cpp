//
//  multisprite.cpp
//  CPSC-4160-Project-2
//
//  Created by Evan Dorn on 2/23/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#include "multisprite.h"
#include "gamedata.h"
#include "frameFactory.h"

void MultiSprite::advanceFrame(Uint32 ticks) {
    timeSinceLastFrame += ticks;
    if (timeSinceLastFrame > frameInterval) {
        currentFrame = (currentFrame+1) % numberOfFrames;
        timeSinceLastFrame = 0;
    }
}

MultiSprite::MultiSprite( const std::string& name) :
Drawable(name,
         Vector2f(Gamedata::getInstance()->getXmlInt(name+"/startLoc/x"),
                  Gamedata::getInstance()->getXmlInt(name+"/startLoc/y")),
         Vector2f(Gamedata::getInstance()->getXmlInt(name+"/speedX"),
                  Gamedata::getInstance()->getXmlInt(name+"/speedY"))
         ),
frames( FrameFactory::getInstance()->getFrames(name) ),
//worldWidth(WORLD_WIDTH),
//worldHeight(WORLD_HEIGHT),

worldWidth(Gamedata :: getInstance()  -> getXmlInt("view/width")),
worldHeight(Gamedata :: getInstance() -> getXmlInt("view/height")),

currentFrame(0),
numberOfFrames( Gamedata::getInstance()->getXmlInt(name+"/frames") ),
frameInterval( Gamedata::getInstance()->getXmlInt(name+"/frameInterval") ),
timeSinceLastFrame( 0 ),
frameWidth(frames[0]->getWidth()),
frameHeight(frames[0]->getHeight())
{ }

MultiSprite::MultiSprite(const MultiSprite& s) :
Drawable(s),
frames(s.frames),
worldWidth( s.worldWidth ),
worldHeight( s.worldHeight ),
currentFrame(s.currentFrame),
numberOfFrames( s.numberOfFrames ),
frameInterval( s.frameInterval ),
timeSinceLastFrame( s.timeSinceLastFrame ),
frameWidth( s.frameWidth ),
frameHeight( s.frameHeight )
{ }

void MultiSprite::draw() const {
    Uint32 x = static_cast<Uint32>(X());
    Uint32 y = static_cast<Uint32>(Y());
    frames[currentFrame]->draw(x, y);
}

void MultiSprite::update(Uint32 ticks) {
    advanceFrame(ticks);
}
