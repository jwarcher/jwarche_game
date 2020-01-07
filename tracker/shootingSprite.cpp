#include "shootingSprite.h"
#include "gameData.h"
#include "imageFactory.h"

ShootingSprite::ShootingSprite(const std::string& name, const Vector2f& pos, int w, int h) :
  SmartSprite(name, pos, w, h),
  Name(name),
  posi(pos),
  we(w),
  he(h),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets( bulletName ),
  bulletName2( Gamedata::getInstance().getXmlStr(name+"/bullet2") ),
  bullets2( bulletName2 ),
  bulletName3( Gamedata::getInstance().getXmlStr(name+"/bullet3") ),
  bullets3( bulletName3 ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedXX") ),
  minSpeed2( Gamedata::getInstance().getXmlInt(bulletName2+"/speedXX") ),
  minSpeed3( Gamedata::getInstance().getXmlInt(bulletName3+"/speedXX") )
{ }

ShootingSprite::ShootingSprite(const ShootingSprite& s) :
  SmartSprite(s.Name, s.posi, s.we, s.he),
  Name(s.Name),
  posi(s.posi),
  we(s.we),
  he(s.he),
  bulletName(s.bulletName),
  bullets(s.bullets),
  bulletName2(s.bulletName2),
  bullets2(s.bullets2),
  bulletName3(s.bulletName3),
  bullets3(s.bullets3),
  minSpeed(s.minSpeed),
  minSpeed2(s.minSpeed2),
  minSpeed3(s.minSpeed3)
{ }

void ShootingSprite::shoot(const int shoot) { 
  //ImageFactory::getInstance(). image.h holds below functions
  float x = getX()+getImage()->getWidth();
  float y = getY()+getImage()->getHeight()/2;
  // I'm not adding minSpeed to y velocity:
 if(shoot == 1){ bullets.shoot( Vector2f(x, y), 
    Vector2f(minSpeed+getVelocityX(), 0)
  );
  }
  if(shoot == 2){ bullets2.shoot( Vector2f(x, y), 
    Vector2f(minSpeed2+getVelocityX(), 0)
  );
  }
  if(shoot == 3){ bullets3.shoot( Vector2f(x, y), 
    Vector2f(minSpeed3+getVelocityX(), 0)
  );
  }
}

bool ShootingSprite::collidedWith(const Drawable* obj, const int collide) const {
  if(collide == 1) return bullets.collidedWith( obj );
  if(collide == 2) return bullets2.collidedWith( obj );
  if(collide == 3) return bullets3.collidedWith( obj );
  else return 0;
}

void ShootingSprite::draw(const int attack) const { 
  SmartSprite::draw();
  if(attack == 1) bullets.draw();
  if(attack == 2) bullets2.draw();
  if(attack == 3) bullets3.draw();
}

void ShootingSprite::drawBullets(const int attack) const { 
  //SmartSprite::draw();
  if(attack == 1) bullets.draw();
  if(attack == 2) bullets2.draw();
  if(attack == 3) bullets3.draw();
}

void ShootingSprite::update(Uint32 ticks, const int up) { 
  SmartSprite::update(ticks);
  if(up == 1) bullets.update(ticks);
  if(up == 2) bullets2.updateWave(ticks);
  if(up == 3) bullets3.updateSpiral(ticks);
}

