//
//  multisprite.h
//  CPSC-4160-Project-2
//
//  Created by Evan Dorn on 2/23/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#ifndef multisprite_h
#define multisprite_h

#include <string>
#include <vector>
#include "drawable.h"

class MultiSprite : public Drawable {
public:
    MultiSprite(const std::string&);
    MultiSprite(const MultiSprite&);
    virtual ~MultiSprite() { }
    
    virtual void draw() const;
    virtual void update(Uint32 ticks);
    virtual const Frame* getFrame() const {
        return frames[currentFrame];
    }
    
protected:
    const std::vector<Frame *> frames;
    int worldWidth;
    int worldHeight;
    
    unsigned currentFrame;
    unsigned numberOfFrames;
    unsigned frameInterval;
    float timeSinceLastFrame;
    int frameWidth;
    int frameHeight;
    
    void advanceFrame(Uint32 ticks);
};

#endif /* multisprite_h */
