#include "player.h"

Player::Player( const std::string& name) :
  OmniMultiSprite(name),
  collision(false),
  initialVelocity(getVelocity())
  { }

Player::Player(const Player& s) :
  OmniMultiSprite(s), 
  collision(s.collision),
  initialVelocity(s.getVelocity())
  { }

Player& Player::operator=(const Player& s) {
  OmniMultiSprite::operator=(s);
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  return *this;
}

void Player::stop() { 
  setVelocity( Vector2f(0, 0) );
  setVelocityX( 0 );
  setVelocityY(0);
  //std::cout << "stop" << std::endl;
  attack = false;
}

void Player::right() { 
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]);
	direction = 1;
	//std::cout << "right" << std::endl;
	attack = false;
  }
} 
void Player::left()  { 
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
	direction = 0;
	//std::cout << "left" << std::endl;
	attack = false;
  }
} 
void Player::up()    { 
  if ( getY() > 0) {
    setVelocityY( -initialVelocity[1] );
	direction = 2;
	//std::cout << "up" << std::endl;
	attack = false;
  }
} 
void Player::down()  { 
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
	direction = 3;
	//std::cout << "down" << std::endl;
	attack = false;
  }
}

void Player::Attack()  { 
	//direction = 100;
	//std::cout << "attack" << std::endl;
	attack = true;
}

void Player::update(Uint32 ticks) {
  if ( !collision ) OmniMultiSprite::update(ticks);
  stop();

}

