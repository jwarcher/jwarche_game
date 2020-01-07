#include "multisprite.h"
#include "gameData.h"
#include "imageFactory.h"
#include "sprite.h"
#include "explodingSprite.h"
#include <math.h>
#include <stdlib.h>

void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

MultiSprite::MultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedXX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedYY"))
           ),
  images( ImageFactory::getInstance().getImages(name) ),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  angle(.01),
  wx(0),
  wy(0),
  set(false),
  explosion(nullptr)
{ }

MultiSprite::MultiSprite(const MultiSprite& s) :
  Drawable(s), 
  images(s.images),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  angle(s.angle),
  wx(s.wx),
  wy(s.wy),
  set(s.set),
  explosion(nullptr)
  { }

MultiSprite& MultiSprite::operator=(const MultiSprite& s) {
  Drawable::operator=(s);
  images = (s.images);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  angle = (s.angle);
  wx = (s.wx);
  wy = (s.wy);
  set = (s.set);
  explosion = (nullptr);
  return *this;
}

MultiSprite::~MultiSprite(){
	delete explosion;
}

inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}

void MultiSprite::draw() const { 
  if(getScale() < SCALE_EPSILON) return;
  if ( explosion ){std::cout << "IM DRAWING" << std::endl; explosion->draw();}
  else{
  	images[currentFrame]->draw(getX(), getY(), getScale());
  }
}

void MultiSprite::explode() {
  Vector2f tempp = getPosition();
  Image* temp = images[currentFrame];
  Sprite sprite(getName(), tempp, getVelocity(), temp);
  if ( !explosion ) explosion = new ExplodingSprite(sprite);
}

void MultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);
  if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    }
    return;
  }
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }  

}

void MultiSprite::updateSpiral(Uint32 ticks) { 
  advanceFrame(ticks);
  if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    }
    return;
  }
	//float x = (2 + 2 * angle) * cos(angle);
	//float y = (2 + 2 * angle) * sin(angle);
	//setX(x);
	//setY(y);
	//Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	//setPosition(getPosition() + incr);
  //Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  //setPosition(getPosition() + incr);
	float ang = 0.0f;
std::cout << "X B4: " << getVelocityX() << " Y B4: " << getVelocityY() << " Angle " << angle << " Ticks " << ticks << " X Coord " << getX() << " Y Coord " << getY() << std::endl;
	ang = 0.1 * angle;
	float x = (10 + 10 * ang) * cos(ang);
	float y = (10 + 10 * ang) * sin(ang);
	angle++;
	if( angle>700) angle = 0.1;
//Vector2f incr(x,y);
//setPosition(getPosition() + (incr * static_cast<float>(ticks) * 0.001));
Vector2f pos(x+Gamedata::getInstance().getXmlInt("Ganon/startLoc/x"),y+Gamedata::getInstance().getXmlInt("Ganon/startLoc/y"));
setPosition(pos);
std::cout << "XAFT: " << getVelocityX() << " Y AFT: " << getVelocityY() << " Angle " << angle << " Ticks " << ticks << " X Coord " << getX() << " Y Coord " << getY() << std::endl;
	
  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }  
//delete pos;
}

void MultiSprite::updateWave(Uint32 ticks) { 
  advanceFrame(ticks);
  if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    }
    return;
  }
	if(!set){
		wx = rand() % Gamedata::getInstance().getXmlInt("view/width");
		set = true;
	}
	wy += rand() % 11;
	Vector2f pos1(wx,wy); 
	setPosition(pos1);
	if(wy >= Gamedata::getInstance().getXmlInt("view/height")) wy = 0;
	//angle+=ang;



  if ( getY() < 0) {
    //setVelocityY( fabs( getVelocityY() ) );
	MultiSprite::explode();
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }  
//delete pos;
}
