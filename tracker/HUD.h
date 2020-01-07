#ifndef HUD__H
#define HUD__H
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "viewport.h"
#include "clock.h"

class Hud {
public:
  static Hud& getInstance();
  //~Hud();
  void writeText(const std::string&, SDL_Color, int, int) const;
  void drawHud();
  SDL_Renderer* getRenderer() const { return renderer; }
 
private:
  int init;
  int x;
  int y;
  int w;
  int h;
  Viewport& viewport;
  Clock& clock;
  SDL_Renderer* renderer;
  TTF_Font* font;
  SDL_Color textColor;
  Hud();
  Hud(const Hud&);
  Hud& operator=(const Hud&);
  
};
#endif
