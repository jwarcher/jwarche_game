#include <SDL_image.h>
#include <sstream>
#include "HUD.h"
#include "gameData.h"
#include "renderContext.h"

Hud& Hud::getInstance() {
  static Hud instance;
  return instance;
}

/*Hud::~Hud() { 
  TTF_CloseFont(font);
  TTF_Quit(); 
}*/

Hud::Hud() : 
  init(TTF_Init()),
  x(Gamedata::getInstance().getXmlInt("hud/x")),  
  y(Gamedata::getInstance().getXmlInt("hud/y")),
  w(Gamedata::getInstance().getXmlInt("hud/w")),
  h(Gamedata::getInstance().getXmlInt("hud/h")),
  viewport(Viewport::getInstance()),
  clock(Clock::getInstance()),
  renderer( RenderContext::getInstance().getRenderer() ),
  font(TTF_OpenFont(Gamedata::getInstance().getXmlStr("font/file").c_str(),
                    Gamedata::getInstance().getXmlInt("font/size"))),
  textColor({0xff, 0, 0, 0})
{
  if ( init == -1 ) {
    throw std::string("error: Couldn't init font");
  }
  if (font == NULL) {
    throw std::string("error: font not found");
  }
  textColor.r = Gamedata::getInstance().getXmlInt("hud/r");
  textColor.g = Gamedata::getInstance().getXmlInt("hud/g");
  textColor.b = Gamedata::getInstance().getXmlInt("hud/b");
  textColor.a = Gamedata::getInstance().getXmlInt("hud/a");
}


void Hud::writeText(const std::string& msg, SDL_Color c, int x, int y) const {
  int textWidth;
  int textHeight;

  SDL_Surface* surface = 
    TTF_RenderText_Solid(font, msg.c_str(), c);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  textWidth = surface->w;
  textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}


void Hud::drawHud() {
    
    //averagefps,secs,x,y,how to play

    int distx = x+5;
    int disty = y+5;

 
    std::stringstream strm2;
    strm2<< "FPS: " << clock.getFps();
    writeText(strm2.str(), textColor,distx, disty+10);
    writeText(Gamedata::getInstance().getXmlStr("hud/str1"), textColor,distx, disty+30);
    writeText(Gamedata::getInstance().getXmlStr("hud/str2"), textColor,distx, disty+50);
    writeText(Gamedata::getInstance().getXmlStr("hud/str3"), textColor,distx, disty+70);
	writeText(Gamedata::getInstance().getXmlStr("hud/str4"), textColor,distx, disty+90);
	writeText(Gamedata::getInstance().getXmlStr("hud/str5"), textColor,distx, disty+120);
	writeText(Gamedata::getInstance().getXmlStr("hud/str6"), textColor,distx, disty+150);
	writeText(Gamedata::getInstance().getXmlStr("hud/str7"), textColor,distx, disty+180);
	writeText(Gamedata::getInstance().getXmlStr("hud/str8"), textColor,distx, disty+210);
	writeText(Gamedata::getInstance().getXmlStr("hud/str9"), textColor,distx, disty+240);
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;

    // set the blend mode so that alpha blending will work;
    // the default blend mode is SDL_BLENDMODE_NONE
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/3 );

    // Render rect
    SDL_RenderFillRect( renderer, &r );

    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderDrawRect( renderer, &r );

  
}
