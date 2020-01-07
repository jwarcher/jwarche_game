#ifndef SHOOTINGSPRITE__H
#define SHOOTINGSPRTIE__H
#include <string>
#include <iostream>
#include "SmartSprite.h"
#include "bulletPool.h"

class ShootingSprite : public SmartSprite {
public:
  ShootingSprite(const std::string& n, const Vector2f& pos, int w, int h);
  ShootingSprite(const ShootingSprite& s);

  virtual void update(Uint32 ticks, const int);
  virtual void draw(const int) const;
   virtual void drawBullets(const int) const;
  void shoot(const int);
  virtual bool collidedWith(const Drawable*, int) const;

private:
  const std::string& Name;
  const Vector2f& posi;
  int we;
  int he;
  std::string bulletName;
  BulletPool bullets;
  std::string bulletName2;
  BulletPool bullets2;
  std::string bulletName3;
  BulletPool bullets3;
  float minSpeed;
  float minSpeed2;
  float minSpeed3;
  ShootingSprite& operator=(const ShootingSprite&);
};

#endif
