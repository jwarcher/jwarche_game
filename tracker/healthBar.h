#ifndef HEALTHBAR__H
#define HEALTHBAR__H
#include "SDL.h"
#include "gameData.h"
#include "clock.h"
#include "drawable2.h"
#include "ioMod.h"

class HealthBar : public Drawable2 {
public:
  HealthBar(const std::string&);
  void draw() const;
  void update(Uint32);
  void reset() { currentLength = barRect.w; }

  HealthBar(const HealthBar&) = delete;
  HealthBar& operator=(const HealthBar&) = delete;

  virtual int getScaledWidth() const  { return barRect.w; }
  virtual int getScaledHeight() const { return barRect.h; }
  virtual const Image* getImage() const { 
    throw std::string("No image in HealthBar");
  }
  virtual int getHealth() const { return currentLength; }
private:
  SDL_Renderer* renderer;
  SDL_Rect barRect;
  Clock& clock;
  int currentLength;
  int increment;  
  float interval; // elapsed time for each decrement (1000ms=1sec)
  int deltaTime;
  std::string Name;
  SDL_Color barColor;
  SDL_Color backColor;
  IoMod& io;
};
#endif
