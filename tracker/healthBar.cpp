#include<sstream>
#include "healthBar.h"
#include "renderContext.h"

HealthBar::HealthBar(const std::string& name) :  
  Drawable2(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc2/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc2/y")), 
           Vector2f(
                    Gamedata::getInstance().getXmlInt(name+"/speedXX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedYY")) 
           ),
  renderer(RenderContext::getInstance().getRenderer()),
  barRect( { Gamedata::getInstance().getXmlInt(name+"/startLoc2/x"),
             Gamedata::getInstance().getXmlInt(name+"/startLoc2/y"),
             Gamedata::getInstance().getXmlInt(name+"/width"),
             Gamedata::getInstance().getXmlInt(name+"/height")}
  ),
  clock( Clock::getInstance() ),
  currentLength(barRect.w), 
  increment(barRect.w/Gamedata::getInstance().getXmlInt(name+"/increment")),
  interval(Gamedata::getInstance().getXmlInt(name+"/interval")),
  deltaTime(0),
  Name(Gamedata::getInstance().getXmlStr(name+"/name")),
  barColor(
    {(Uint8)Gamedata::getInstance().getXmlInt(name+"/barColor/r"),
     (Uint8)Gamedata::getInstance().getXmlInt(name+"/barColor/g"),
     (Uint8)Gamedata::getInstance().getXmlInt(name+"/barColor/b"),
     (Uint8)Gamedata::getInstance().getXmlInt(name+"/barColor/a")}
  ),
  backColor(
    {(Uint8)Gamedata::getInstance().getXmlInt(name+"/backColor/r"),
     (Uint8)Gamedata::getInstance().getXmlInt(name+"/backColor/g"),
     (Uint8)Gamedata::getInstance().getXmlInt(name+"/backColor/b"),
     (Uint8)Gamedata::getInstance().getXmlInt(name+"/backColor/a")}
  ),
  io( IoMod::getInstance() )
{}

void HealthBar::update(Uint32 ticks) {
  deltaTime += ticks;
  //if ( currentLength > 0 && deltaTime > interval ) {//change to collision here
    //deltaTime = 0;
	if(currentLength - increment < 0) currentLength = 0;
    else currentLength -= increment;
  //}
}

void HealthBar::draw() const {
  // First set the blend mode so that alpha blending will work;
  // the default blend mode is SDL_BLENDMODE_NONE!
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  // Set the health bar background color:
  SDL_SetRenderDrawColor( 
    renderer, backColor.r, backColor.g, backColor.b, backColor.a );
  // Draw the  background
  SDL_RenderFillRect( renderer, &barRect );

  SDL_SetRenderDrawColor( 
    renderer, barColor.r, barColor.g, barColor.b, barColor.a );
  int x = static_cast<int>(getX());
  int y = static_cast<int>(getY());
  io.writeText(Name, x, y-22, {255,255,255,255});
  SDL_Rect healthRect = {x, y, currentLength, barRect.h};
  SDL_RenderFillRect( renderer, &healthRect );

  // Set the  color for the health bar outline:
  SDL_SetRenderDrawColor( 
    renderer, barColor.r, barColor.g, barColor.b, barColor.a );
  SDL_RenderDrawRect( renderer, &barRect );
}

