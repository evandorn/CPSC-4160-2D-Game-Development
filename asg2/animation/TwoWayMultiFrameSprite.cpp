//
//  TwoWayMultiFrameSprite.c
//  CPSC-4160-Project-2
//
//  Created by Evan Dorn on 2/23/16.
//  Copyright © 2016 evandorn. All rights reserved.
//
#include <iostream>
#include <cmath>
#include "TwoWayMultiFrameSprite.h"
#include "gamedata.h"
#include "frameFactory.h"

void TwoWayMultiFrameSprite::advanceFrame(Uint32 ticks) {
    timeSinceLastFrame += ticks;
    if (timeSinceLastFrame > frameInterval) {
        currentFrame = (currentFrame+1) % numberOfFrames;
        timeSinceLastFrame = 0;
    }
}

TwoWayMultiFrameSprite::TwoWayMultiFrameSprite( const std::string& name) :
Drawable(name,
         Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                  Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
         Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                  Gamedata::getInstance().getXmlInt(name+"/speedY"))
         ),
framesLeft( FrameFactory::getInstance().getFrames(name+"/left") ),
framesRight( FrameFactory::getInstance().getFrames(name) ),
frames(framesRight),
worldWidth(Gamedata::getInstance().getXmlInt("world/worldWidth")),
worldHeight(Gamedata::getInstance().getXmlInt("world/worldHeight")),

dt(0),
currentFrame(0),
numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
timeSinceLastFrame( 0 ),
frameWidth(frames[0]->getWidth()),
frameHeight(frames[0]->getHeight())
{ }

TwoWayMultiFrameSprite::TwoWayMultiFrameSprite(const std::string& name,
                                     const Vector2f& pos, const Vector2f& vel,
                                     const std::vector<Frame*>& fmsLeft,const std::vector<Frame*>& fmsRight) :
Drawable(name, pos, vel),
framesLeft(fmsLeft),
framesRight(fmsRight),
frames(fmsRight),
worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),

dt(0),
currentFrame(0),
 numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
timeSinceLastFrame( 0 ),
frameWidth(fmsRight[0]->getWidth()),
frameHeight(fmsRight[0]->getHeight())
{ }

TwoWayMultiFrameSprite::TwoWayMultiFrameSprite(const TwoWayMultiFrameSprite& s) :
Drawable(s.getName(), s.getPosition(), s.getVelocity()),
framesLeft(s.framesLeft),
framesRight(s.framesRight),
frames(s.frames),
worldWidth( s.worldWidth ),
worldHeight( s.worldHeight ),
dt(s.dt),
currentFrame(s.currentFrame),
numberOfFrames( s.numberOfFrames ),
frameInterval( s.frameInterval ),
timeSinceLastFrame( s.timeSinceLastFrame ),
frameWidth( s.frameWidth ),
frameHeight( s.frameHeight )
{ }


void TwoWayMultiFrameSprite::draw() const {
    Uint32 x = static_cast<Uint32>(X());
    Uint32 y = static_cast<Uint32>(Y());
    frames[currentFrame]->draw(x, y);
}

void TwoWayMultiFrameSprite::update(Uint32 ticks) {
    advanceFrame(ticks);
    
    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    setPosition(getPosition() + incr);
    
    if ( Y() < 0) {
        velocityY( abs( velocityY() ) );
    }
    if ( Y() > worldHeight-frameHeight) {
        velocityY( -abs( velocityY() ) );
    }
    
    if ( X() < 0) {
        velocityX( abs( velocityX() ) );
        
        frames = framesRight;
    }
    if ( X() > worldWidth-frameWidth) {
        velocityX( -abs( velocityX() ) );
        
        frames = framesLeft;
    }  
}
