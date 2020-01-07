#ifndef GANON__H
#define GANON__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class ExplodingSprite;

class Ganon : public Drawable {
public:
  Ganon(const std::string&);
  Ganon(const Ganon&);
  ~Ganon();

  virtual void draw() const;
  virtual void hitdraw() const;
  virtual void movedraw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { 
    return images[currentFrame]; 
  }
  int getScaledWidth()  const { 
    return getScale()*images[currentFrame]->getWidth(); 
  } 
  int getScaledHeight()  const { 
    return getScale()*images[currentFrame]->getHeight(); 
  } 
  virtual const SDL_Surface* getSurface() const { 
    return images[currentFrame]->getSurface();
  }
  virtual void explode();
protected:
  std::vector<Image *> images;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  mutable bool move;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;
  ExplodingSprite* explosion;

  void advanceFrame(Uint32 ticks);
  Ganon& operator=(const Ganon&);
};
#endif
