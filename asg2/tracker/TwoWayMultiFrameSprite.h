//
//  TwoWayMultiFrameSprite.h
//  
//
//  Created by Evan Dorn on 3/6/16.
//
//

#ifndef TwoWayMultiFrameSprite_h
#define TwoWayMultiFrameSprite_h

#include <string>
#include <vector>
#include "multisprite.h"


#include <string>
#include <iostream>
#include <vector>
#include "drawable.h"

class TwoWayMultiFrameSprite : public Drawable {
public:
    TwoWayMultiFrameSprite(const std::string& n,
                           std::vector<Frame*>& fmsLeft,
                           std::vector<Frame*>& fmsRight, const float sc);
    TwoWayMultiFrameSprite(const TwoWayMultiFrameSprite& s);
    virtual ~TwowayMultiframeSprite() { }
    virtual const Frame* getFrame() const { return frames[currentFrame]; }
    
    virtual void draw() const;
    virtual void update(Uint32 ticks);
    unsigned getPixel(Uint32, Uint32) const;
    
private:
    std::vector<Frame *> framesLeft;
    std::vector<Frame *> framesRight;
    std::vector<Frame *> frames;
    int frameWidth;
    int frameHeight;
    int worldWidth;
    int worldHeight;
    float dt;
    unsigned currentFrame;
    unsigned numberOfFrames;
    unsigned frameInterval;
    void advanceFrame(Uint32 ticks);
    TwoWayMultiFrameSprite& operator=(const TwoWayMultiFrameSprite&);
};

#endif /* TwoWayMultiFrameSprite_h */
