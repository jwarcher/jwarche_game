#include "SubSprite.h"
#include "SmartSprite.h"
#include "gameData.h"
#include "renderContext.h"


SubjectSprite::SubjectSprite( const std::string& name) :
  Player(name), 
  //str(name),
  //hb(str),
  observers()
{ }

SubjectSprite::SubjectSprite(const SubjectSprite& s) :
  Player(s),
  //str(s.str),
  //hb(s.hb), 
  observers( s.observers )
  { }

void SubjectSprite::detach( SmartSprite* o ) {
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}
/*
void SubjectSprite::draw(){
	hb.draw();
}
*/
void SubjectSprite::update(Uint32 ticks) { 
  Player::update(ticks);
  //hb.update(ticks);
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    int offset = rand()%5;
    offset = offset*(rand()%2?-1:1);
    const Vector2f off(offset, offset);
    (*ptr)->setPlayerPos( getPosition()+off );
    ++ptr;
  }
}
