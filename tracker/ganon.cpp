#include "ganon.h"
#include "gameData.h"
#include "imageFactory.h"
#include "sprite.h"
#include "explodingSprite.h"

void Ganon::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
		if(move){
    	currentFrame = (currentFrame+1) % numberOfFrames;
			timeSinceLastFrame = 0;
		}
		else{
		currentFrame = (currentFrame+1) % 8;
			timeSinceLastFrame = 0;
		}
	}
}

Ganon::Ganon( const std::string& name) :
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
  move(false),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  explosion(nullptr)
{ }

Ganon::Ganon(const Ganon& s) :
  Drawable(s), 
  images(s.images),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  move(s.move),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  explosion(nullptr)
  { }

Ganon::~Ganon(){
	delete explosion;
}

Ganon& Ganon::operator=(const Ganon& s) {
  Drawable::operator=(s);
  images = (s.images);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  move = (s.move);
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  explosion = (nullptr);
  return *this;
}

inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}

void Ganon::hitdraw() const {
if(getScale() < SCALE_EPSILON) return;
  if ( explosion ){ explosion->draw();}
  else{
	//std::cout << "IM GETTING HIT" << std::endl;
	images[9]->draw(getX(), getY(), getScale());
	move = true;
  }
}

void Ganon::movedraw() const {
if(getScale() < SCALE_EPSILON) return;
  if ( explosion ) explosion->draw();
  else{
	//std::cout << "IM MOVING" << std::endl;
	images[8]->draw(getX(), getY(), getScale());
	move = true;
  }
}

void Ganon::draw() const { 
  if(getScale() < SCALE_EPSILON) return;
  if ( explosion ){std::cout << "IM DRAWING" << std::endl; explosion->draw();}
  else{
	images[currentFrame]->draw(getX(), getY(), getScale());
	move = false;
  }
}

void Ganon::explode() {
  //std::cout << "BLLLLLAHHHHHHHAAAHAAHHA" << std::endl;
  Vector2f tempp = getPosition();
  Image* temp = images[currentFrame];
  Sprite sprite(getName(), tempp, getVelocity(), temp);
  if ( !explosion ){std::cout << "IM IN IT" << std::endl; explosion = new ExplodingSprite(sprite);}
}

void Ganon::update(Uint32 ticks) { 
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
