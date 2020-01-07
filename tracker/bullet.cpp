#include <iostream>
#include <cmath>
#include "bullet.h"
#include "CollisionStrategy.h"

void Bullet::update(Uint32 ticks) { 
  Vector2f pos = getPosition();
  MultiSprite::update(ticks);
  distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
  if (distance > maxDistance) tooFar = true;
}

void Bullet::updateSpiral(Uint32 ticks) { 
  Vector2f pos = getPosition();
  MultiSprite::updateSpiral(ticks);
  distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
  if (distance > maxDistance) tooFar = true;
}

void Bullet::updateWave(Uint32 ticks) { 
  Vector2f pos = getPosition();
  MultiSprite::updateWave(ticks);
  distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
  if (distance > maxDistance) tooFar = true;
}

