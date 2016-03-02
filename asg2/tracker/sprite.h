//
//  sprite.h
//  CPSC-4160-Project-2
//
//  Created by Evan Dorn on 2/23/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#ifndef sprite_h
#define sprite_h

#include <string>

#include "drawable.h"

class Sprite : public Drawable {
public:
    Sprite(const std::string&);
    Sprite(const std::string&, const Vector2f& pos, const Vector2f& vel);
    Sprite(const std::string&,
           const Vector2f& pos, const Vector2f& vel, const Frame*);
    Sprite(const Sprite& s);
    virtual ~Sprite() { }
    
    virtual const Frame* getFrame() const { return frame; }
    virtual void draw() const;
    
    virtual void update(Uint32 ticks);
    
private:
    const Frame * frame;
    int frameWidth;
    int frameHeight;
    int worldWidth;
    int worldHeight;
    int getDistance(const Sprite*) const;
};

#endif /* sprite_h */
