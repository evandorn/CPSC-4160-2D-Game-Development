#ifndef SPRITE__H
#define SPRITE__H
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

  Sprite& operator=(const Sprite& rhs) {
    Drawable::operator=(rhs);
    frame = rhs.frame;
    frameWidth = rhs.frameWidth;
    frameHeight = rhs.frameHeight;
    worldWidth = rhs.worldWidth;
    worldHeight = rhs.worldHeight;
    return *this;
  } 


private:
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int getDistance(const Sprite*) const;
};
#endif
