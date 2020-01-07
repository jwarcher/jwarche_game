#ifndef SUBSPRITE__H
#define SUBSPRITE__H

#include <string>
#include <list>
#include <cmath>
#include "player.h"
#include "healthBar.h"

class SmartSprite;
class HealthBar;

class SubjectSprite : public Player {
public:
  SubjectSprite(const std::string&);
  SubjectSprite(const SubjectSprite&);

  void update(Uint32 ticks);
  void attach( SmartSprite* o ) { observers.push_back(o); } 
  void detach( SmartSprite* o );
  //void draw();

protected:
  //const std::string& str;
  //const HealthBar& hb;
  std::list<SmartSprite*> observers;
  SubjectSprite& operator=(const SubjectSprite&);
};
#endif
