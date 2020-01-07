#include "omnimultisprite.h"
#include "sprite.h"
#include "gameData.h"
#include "imageFactory.h"
#include "explodingSprite.h"



void OmniMultiSprite::advanceFrame(Uint32 ticks) {
	//std::cout << timeSinceLastFrame << " " << currentFrame << std::endl;
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
		if(direction == 2 || direction == 3){
		currentFrame = (currentFrame+1) % (numberOfFrames/10);
		}
		else{
    currentFrame = (currentFrame+1) % (numberOfFrames/20);
		}
		timeSinceLastFrame = 0;
	}
	
}

OmniMultiSprite::OmniMultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  images( ImageFactory::getInstance().getImages(name) ),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  direction(7),
  attack(false),
  explosion(nullptr)
{ }

OmniMultiSprite::OmniMultiSprite(const OmniMultiSprite& s) :
  Drawable(s), 
  images(s.images),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  direction(s.direction),
  attack(false),
  explosion(nullptr)
  { }

OmniMultiSprite::~OmniMultiSprite(){
	delete explosion;
}

OmniMultiSprite& OmniMultiSprite::operator=(const OmniMultiSprite& s) {
  Drawable::operator=(s);
  images = (s.images);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  direction = (s.direction);
  attack = false;
  explosion = (nullptr);
  return *this;
}

inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}

void OmniMultiSprite::draw() const { 
//std::cout << "Direction " << direction << " VX " << getVelocityX() << " VY " << getVelocityY() << " Attack " << attack << " current frame " << currentFrame << std::endl;
	if(getScale() < SCALE_EPSILON) return;
  if ( explosion ) explosion->draw();
  else{ 

	if (direction == 0 && getVelocityX() < 0 && getVelocityY() == 0 && attack == false){
  images[numberOfFrames-(4+currentFrame)]->draw(getX(), getY(), getScale());
	}
	else if (direction == 1 && getVelocityX() > 0 && getVelocityY() == 0 && attack == false){
  images[numberOfFrames-(19+currentFrame)]->draw(getX(), getY(), getScale());
	}
	else if (direction == 2 && getVelocityX() == 0 && getVelocityY() < 0 && attack == false){
  images[numberOfFrames-(25+currentFrame)]->draw(getX(), getY(), getScale());
	}
	else if (direction == 3 && getVelocityX() == 0 && getVelocityY() > 0 && attack == false){
  images[numberOfFrames-(10+currentFrame)]->draw(getX(), getY(), getScale());
	}
	else if (getVelocityX() > 0 && getVelocityY() > 0 && attack == false){
  images[numberOfFrames-(16+currentFrame)]->draw(getX(), getY(), getScale());
  direction = 5;
  //direction = -1;
	}
	else if (getVelocityX() > 0 && getVelocityY() < 0 && attack == false){
  images[numberOfFrames-(22+currentFrame)]->draw(getX(), getY(), getScale());
  direction = 4;
  //direction = -1;
	}
	else if (getVelocityX() < 0 && getVelocityY() < 0 && attack == false){
  images[numberOfFrames-(1+currentFrame)]->draw(getX(), getY(), getScale());
  direction = 7;
  //direction = -1;
	}
	else if (getVelocityX() < 0 && getVelocityY() > 0 && attack == false){
  images[numberOfFrames-(7+currentFrame)]->draw(getX(), getY(), getScale());
  direction = 6;
  //direction = -1;
	}
	else if (direction == 0 && getVelocityX() == 0 && getVelocityY() == 0 && attack == false){
  images[56]->draw(getX(), getY(), getScale());
	}
	else if (direction == 1 && getVelocityX() == 0 && getVelocityY() == 0 && attack == false){
  images[39]->draw(getX(), getY(), getScale());
	}
	else if (direction == 2 && getVelocityX() == 0 && getVelocityY() == 0 && attack == false){
  images[30]->draw(getX(), getY(), getScale());
	}
	else if (direction == 3 && getVelocityX() == 0 && getVelocityY() == 0 && attack == false){
  images[48]->draw(getX(), getY(), getScale());
	}
	else if (direction == 4 && getVelocityX() == 0 && getVelocityY() == 0 && attack == false){
  images[36]->draw(getX(), getY(), getScale());
	}
	else if (direction == 5 && getVelocityX() == 0 && getVelocityY() == 0 && attack == false){
  images[43]->draw(getX(), getY(), getScale());
	}
	else if (direction == 6 && getVelocityX() == 0 && getVelocityY() == 0 && attack == false){
  images[52]->draw(getX(), getY(), getScale());
	}
	else if (direction == 7 && getVelocityX() == 0 && getVelocityY() == 0 && attack == false){
  images[58]->draw(getX(), getY(), getScale());
	}

	//attack frames

	else if (direction == 0 && getVelocityX() < 0 && getVelocityY() == 0 && attack == true){
  images[numberOfFrames-(34+currentFrame)]->draw(getX(), getY(), getScale());
	//std::cout << "ATTACK LEFT" << std::endl;
	} 
	else if (direction == 1 && getVelocityX() > 0 && getVelocityY() == 0 && attack == true){
  images[numberOfFrames-(49+currentFrame)]->draw(getX(), getY(), getScale());
//std::cout << "ATTACK RIGHT" << std::endl;
	}
	else if (direction == 2 && getVelocityX() == 0 && getVelocityY() < 0 && attack == true){
  //std::cout << "ATTACK UP" << std::endl;
  images[numberOfFrames-(55+currentFrame)]->draw(getX(), getY(), getScale());
	}
	else if (direction == 3 && getVelocityX() == 0 && getVelocityY() > 0 && attack == true){
  images[numberOfFrames-(40+currentFrame)]->draw(getX(), getY(), getScale());
//std::cout << "ATTACK DOWN" << std::endl;
	}
	else if (getVelocityX() > 0 && getVelocityY() > 0 && attack == true){
  images[numberOfFrames-(46+currentFrame)]->draw(getX(), getY(), getScale());
//std::cout << "ATTACK DOWN RIGHT" << std::endl;
  direction = 5;
  //direction = -1;
	}
	else if (getVelocityX() > 0 && getVelocityY() < 0 && attack == true){
  images[numberOfFrames-(52+currentFrame)]->draw(getX(), getY(), getScale());
//std::cout << "ATTACK UP RIGHT" << std::endl;
  direction = 4;
  //direction = -1;
	}
	else if (getVelocityX() < 0 && getVelocityY() < 0 && attack == true){
  images[numberOfFrames-(31+currentFrame)]->draw(getX(), getY(), getScale());
//std::cout << "ATTACK UP LEFT" << std::endl;
  direction = 7;
  //direction = -1;
	}
	else if (getVelocityX() < 0 && getVelocityY() > 0 && attack == true){
  images[numberOfFrames-(37+currentFrame)]->draw(getX(), getY(), getScale());
//std::cout << "ATTACK DOWN LEFT" << std::endl;
  direction = 6;
  //direction = -1;
	}
	else if (direction == 0 && getVelocityX() == 0 && getVelocityY() == 0 && attack == true){
  images[26]->draw(getX(), getY(), getScale());
	}
	else if (direction == 1 && getVelocityX() == 0 && getVelocityY() == 0 && attack == true){
  images[9]->draw(getX(), getY(), getScale());
	}
	else if (direction == 2 && getVelocityX() == 0 && getVelocityY() == 0 && attack == true){
  images[0]->draw(getX(), getY(), getScale());
	}
	else if (direction == 3 && getVelocityX() == 0 && getVelocityY() == 0 && attack == true){
  images[18]->draw(getX(), getY(), getScale());
	}
	else if (direction == 4 && getVelocityX() == 0 && getVelocityY() == 0 && attack == true){
  images[6]->draw(getX(), getY(), getScale());
	}
	else if (direction == 5 && getVelocityX() == 0 && getVelocityY() == 0 && attack == true){
  images[13]->draw(getX(), getY(), getScale());
	}
	else if (direction == 6 && getVelocityX() == 0 && getVelocityY() == 0 && attack == true){
  images[22]->draw(getX(), getY(), getScale());
	}
	else if (direction == 7 && getVelocityX() == 0 && getVelocityY() == 0 && attack == true){
  images[28]->draw(getX(), getY(), getScale());
	}

}
//std::cout << direction << " " << direction2 << " " << getVelocityX() << " " << getVelocityY() << " " << currentFrame << std::endl;
}

void OmniMultiSprite::explode() {
  Vector2f tempp = getPosition();
  Image* temp = images[currentFrame];
  Sprite sprite(getName(), tempp, getVelocity(), temp);
  if ( !explosion ) explosion = new ExplodingSprite(sprite);
}

void OmniMultiSprite::update(Uint32 ticks) { 
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
	//direction = 1;
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
	//direction = 0;
  }  

}
