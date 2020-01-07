#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "ganon.h"
#include "twowaymultisprite.h"
#include "omnimultisprite.h"
#include "gameData.h"
#include "engine.h"
#include "player.h"
#include "shootingSprite.h"
#include "frameGenerator.h"
#include "CollisionStrategy.h"
#include "SubSprite.h"
#include "SmartSprite.h"


Engine::~Engine() { 
  for(auto& w : deadGanon) delete w;
  for(auto& x : ganon) delete x;
  ganon.clear();
	for(auto& y : strategies) delete y;
	strategies.clear();
	delete player;
	if(playerNum) delete player2;
	delete healthBar;
    delete healthBar2;
	delete GanonHealth;
	delete BigFish;
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine(bool a) :
  gdata(Gamedata::getInstance()),
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc.getRenderer() ),
  world("back", Gamedata::getInstance().getXmlInt("back/factor")),
  world2("back2", Gamedata::getInstance().getXmlInt("back/factor")),
  world3("back3", Gamedata::getInstance().getXmlInt("back/factor")),
  viewport( Viewport::getInstance() ),
  player(new SubjectSprite("Link1")),
  player2(new SubjectSprite("Link2")),
  ganon(),
  deadGanon(),
  strategies(),
  currentStrategy(0),
  hud(Hud::getInstance()),
  collision(false),
  playerNum(a),
  playerNumCheck(false),
  Music(false),
  godMode(false),
  HitMarker(false),
  HitMarker2(false),
  start(std::chrono::system_clock::now() ),
  start2(std::chrono::system_clock::now() ),
  end(std::chrono::system_clock::now() ),
  beginClock(std::chrono::system_clock::now()),
  healthBar(new HealthBar("HealthBar")),
  healthBar2(new HealthBar("HealthBar2")),
  GanonHealth(new HealthBar("GanonHealth")),
  BigFish(new SDLSound()),

  
  currentSprite(0),
   hudFlag(true),
  makeVideo(false)
{

ganon.reserve(1);
Vector2f pos = player->getPosition();
int w = player->getScaledWidth();
int h = player->getScaledHeight();

		ganon.push_back(new ShootingSprite("Ganon", pos, w, h));
		player->attach(ganon[0]);
		if(playerNum) player2->attach(ganon[0]);

  strategies.push_back( new PerPixelCollisionStrategy );
  Viewport::getInstance().setObjectToTrack(player);
  if(playerNum) Viewport::getInstance().setObjectToTrack(player2);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
std::stringstream ss;
ss << gdata.getXmlStr("username2");

  world.draw();
  //time(&end);
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::chrono::duration<double> elapsed_seconds2 = end - start2;
  std::chrono::duration<double> elapsed_seconds3 = end - beginClock;
  
 for ( auto* sprite : ganon ) {
	if(GanonHealth->getHealth() > gdata.getXmlInt("GanonHealth/Phase2")){

		if((std::fmod(elapsed_seconds3.count(),gdata.getXmlInt("Ganon/AttackInterval"))) > gdata.getXmlInt("Ganon/ShootWaitSeconds")) {
		sprite->draw(1);		
		sprite->shoot(1);
		}
		else{static_cast<Ganon*>(ganon[0])->movedraw(); sprite->drawBullets(1);}
		//else if( elapsed_seconds3.count() > 25){GanonShootTime(GanonShootTime);}
	}
	if((GanonHealth->getHealth() > gdata.getXmlInt("GanonHealth/Phase3")) && (GanonHealth->getHealth() <= gdata.getXmlInt("GanonHealth/Phase2"))){

    	if((std::fmod(elapsed_seconds3.count(),gdata.getXmlInt("Ganon/AttackInterval"))) > gdata.getXmlInt("Ganon/ShootWaitSeconds")) {
		sprite->draw(2);		
		sprite->shoot(2);
		}
		else{static_cast<Ganon*>(ganon[0])->movedraw(); sprite->drawBullets(2);}
	}
	if((GanonHealth->getHealth() > 0) && (GanonHealth->getHealth() <= gdata.getXmlInt("GanonHealth/Phase3"))){
    	if((std::fmod(elapsed_seconds3.count(),gdata.getXmlInt("Ganon/AttackInterval"))) > gdata.getXmlInt("Ganon/ShootWaitSeconds")) {
		sprite->draw(3);		
		sprite->shoot(3);
		}
		else{static_cast<Ganon*>(ganon[0])->movedraw(); sprite->drawBullets(3);}
	}
  }
  for ( auto* sprite : deadGanon ) {
    sprite->draw(0);
	world3.draw();
	//sprite->shoot();
  }

if( (healthBar->getHealth() != 0) || elapsed_seconds.count() < 2.5 || HitMarker == false) player->draw();
  if((playerNum && (healthBar2->getHealth() != 0))  || (playerNum && elapsed_seconds2.count() < 2.5) || (playerNum && HitMarker2 == false)) player2->draw();

  if(hudFlag == true) {
    hud.drawHud();
}
  healthBar->draw();
  if(playerNum) healthBar2->draw();
  GanonHealth->draw();

  if(playerNum){
  	if((healthBar->getHealth() == 0) && (healthBar2->getHealth() == 0)){
		world2.draw(); 
  	}
  }
  else{
	if(healthBar->getHealth() == 0){
		world2.draw();
	}
  }
  //static_cast<SubjectSprite*>(player)->draw();
  //static_cast<SubjectSprite*>(player2)->draw();
  viewport.draw();
  io.writeText(ss.str(), 25, gdata.getXmlInt("view/height")- 50, {255,0,0,255});
  SDL_RenderPresent(renderer); 
}

void Engine::update(Uint32 ticks) {
  if((playerNum == false) && (playerNumCheck == false)){
	//std::cout << "SDKSDFD" << std::endl; 
	delete player2;
  }
	//std::cout << "SDKSDFD" << std::endl;
  playerNumCheck = true;
  auto it = ganon.begin();
while ( it != ganon.end()) {
	if(playerNum){
    	if ( ((strategies[0]->execute(*player, **it)) && (healthBar->getHealth() != 0) && (static_cast<OmniMultiSprite*>(player)->getAttack())) 
			|| ((strategies[0]->execute(*player2, **it)) && (healthBar2->getHealth() != 0) && (static_cast<Player*>(player2)->getAttack()))) {
	 	 	if(GanonHealth->getHealth() == 0){
				static_cast<Ganon*>(ganon[0])->explode();
      			SmartSprite* doa = *it;
      			player->detach(doa);
	  			player2->detach(doa);
        		deadGanon.push_back((*it));
      			//delete doa;
      			it = ganon.erase(it);
				if(Music){BigFish->stopMusic3(); BigFish->startMusic4(); Music = false; std::cout << "MUSSSSIIICICICIICIC" << std::endl;}
    		}
	 	 	else{
				static_cast<Ganon*>(ganon[0])->hitdraw();
				GanonHealth->update(ticks);
				//std::cout << GanonHealth->getHealth() << std::endl;
				break;
		 	}
		}
		else ++it;
    }
	else{
		if ( ((strategies[0]->execute(*player, **it)) && (healthBar->getHealth() != 0) && (static_cast<OmniMultiSprite*>(player)->getAttack()))){
	 	 	if(GanonHealth->getHealth() == 0){
				static_cast<Ganon*>(ganon[0])->explode();
      			SmartSprite* doa = *it;
      			player->detach(doa);
        		deadGanon.push_back((*it));
      			//delete doa;
      			it = ganon.erase(it);
				if(Music){BigFish->stopMusic3(); BigFish->startMusic4(); Music = false; std::cout << "MUSSSSIIICICICIICIC" << std::endl;}
    		}
	 	 	else{
				static_cast<Ganon*>(ganon[0])->hitdraw();
				GanonHealth->update(ticks);
				//std::cout << GanonHealth->getHealth() << std::endl;
				break;
		 	}
		
    	 }
		else ++it;
	}
}
//std::cout << "SDKSDFD" << std::endl;
for (auto* sprite : ganon){
  if(GanonHealth->getHealth() > gdata.getXmlInt("GanonHealth/Phase2")){
	if(!Music){BigFish->startMusic(); Music = true;}
	if(sprite->collidedWith(player, 1)){ 
		if(!godMode) healthBar->update(ticks);
		else{}
		if(healthBar->getHealth() == 0 && HitMarker == false) {
			static_cast<OmniMultiSprite*>(player)->explode();
			start = std::chrono::system_clock::now();
			player->detach(ganon[0]);
			HitMarker = true;
		}
		//static_cast<MultiSprite*>(sprite)->explode();
	}
	if(playerNum){
  		if(sprite->collidedWith(player2, 1)){ 
			if(!godMode) healthBar2->update(ticks);
			else{}
			if(healthBar2->getHealth() == 0 && HitMarker2 == false) {
				static_cast<OmniMultiSprite*>(player2)->explode();
				start2 = std::chrono::system_clock::now();
				player2->detach(ganon[0]);
				HitMarker2 = true;
			//static_cast<MultiSprite*>(sprite)->explode();
			}
  		}
  	}
  }
  if((GanonHealth->getHealth() > gdata.getXmlInt("GanonHealth/Phase3")) && (GanonHealth->getHealth() <= gdata.getXmlInt("GanonHealth/Phase2"))){
		if(Music){BigFish->stopMusic(); BigFish->startMusic2(); Music = false; std::cout << "MUSSSSIIICICICIICIC" << std::endl;}
    	if(sprite->collidedWith(player, 2)){ 
		if(!godMode) healthBar->update(ticks);
		else{}
		if(healthBar->getHealth() == 0 && HitMarker == false) {
				static_cast<OmniMultiSprite*>(player)->explode();
				start = std::chrono::system_clock::now();
				player->detach(ganon[0]);
				HitMarker = true;
		}
		//static_cast<MultiSprite*>(sprite)->explode();
	}
	if(playerNum){
  		if(sprite->collidedWith(player2, 2)){ 
			if(!godMode) healthBar2->update(ticks);
			else{}
			if(healthBar2->getHealth() == 0 && HitMarker2 == false) {
				static_cast<OmniMultiSprite*>(player2)->explode();
				start2 = std::chrono::system_clock::now();
				player2->detach(ganon[0]);
				HitMarker2 = true;
			//static_cast<MultiSprite*>(sprite)->explode();
			}
			//static_cast<MultiSprite*>(sprite)->explode();
  		}
 	 }
  }
  if((GanonHealth->getHealth() > 0) && (GanonHealth->getHealth() <= gdata.getXmlInt("GanonHealth/Phase3"))){
		if(!Music){BigFish->stopMusic2(); BigFish->startMusic3(); Music = true; std::cout << "MUSSSSIIICICICIICIC" << std::endl;}
    	if(sprite->collidedWith(player, 3)){ 
		if(!godMode) healthBar->update(ticks);
		else{}
		if(healthBar->getHealth() == 0 && HitMarker == false) {
				static_cast<OmniMultiSprite*>(player)->explode();
				start = std::chrono::system_clock::now();
				player->detach(ganon[0]);
				HitMarker = true;
			//static_cast<MultiSprite*>(sprite)->explode();
		}
		//static_cast<MultiSprite*>(sprite)->explode();
		}
	if(playerNum){
  		if(sprite->collidedWith(player2, 3)){ 
			if(!godMode) healthBar2->update(ticks);
			else{}
			if(healthBar2->getHealth() == 0 && HitMarker == false) {
				static_cast<OmniMultiSprite*>(player2)->explode();
				start2 = std::chrono::system_clock::now();
				player2->detach(ganon[0]);
				HitMarker2 = true;
			//static_cast<MultiSprite*>(sprite)->explode();
			}
			//static_cast<MultiSprite*>(sprite)->explode();
		}
  	}
  }
}

player->update(ticks);
if(playerNum) player2->update(ticks);
  
  
  for ( auto* sprite : ganon ) {
    if(GanonHealth->getHealth() > gdata.getXmlInt("GanonHealth/Phase2")){
		sprite->update( ticks, 1 );
	}
	if((GanonHealth->getHealth() > gdata.getXmlInt("GanonHealth/Phase3")) && (GanonHealth->getHealth() <= gdata.getXmlInt("GanonHealth/Phase2"))){
    	sprite->update( ticks, 2 );
	}
	if((GanonHealth->getHealth() > 0) && (GanonHealth->getHealth() <= gdata.getXmlInt("GanonHealth/Phase3"))){
    	sprite->update( ticks, 3 );
	}
  }
  for ( auto* sprite : deadGanon ) {
    //world3.update();
    sprite->update( ticks, 1 );
  }
  world.update();
  	if(playerNum){
    	if((healthBar->getHealth() == 0) && (healthBar2->getHealth() == 0)) {
        	if(deadGanon.size() == 1) world3.update();
    	//sprite->update( ticks );
		}
  	}
  	else{
		if((healthBar->getHealth() == 0)) {
        	if(deadGanon.size() == 1) world3.update();
    	//sprite->update( ticks );
		}
  	}
    end = std::chrono::system_clock::now();
  viewport.update(); // always update viewport last


}

bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
		if (keystate[SDL_SCANCODE_G]) {
    	    if(!godMode) godMode = true;
			else godMode = false;
      }
        if ( keystate[SDL_SCANCODE_T] ) {
          //switchSprite();
        }
		if (keystate[SDL_SCANCODE_F1]) {
	  		if(hudFlag == false) {
            hudFlag = true;
          }
          else if(hudFlag == true) {
            hudFlag = false;
			}
	  }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
	  if (keystate[SDL_SCANCODE_R]) {
        SDL_Delay(10);
		return true;
      }
	  if (keystate[SDL_SCANCODE_A]) {
        static_cast<Player*>(player)->left();
      }
      if (keystate[SDL_SCANCODE_D]) {
        static_cast<Player*>(player)->right();
      }
      if (keystate[SDL_SCANCODE_W]) {
        static_cast<Player*>(player)->up();
      }
      if (keystate[SDL_SCANCODE_S]) {
        static_cast<Player*>(player)->down();
      }
	  if (keystate[SDL_SCANCODE_SPACE]) {
        static_cast<Player*>(player)->Attack();
      }
      if(playerNum){
	  	if (keystate[SDL_SCANCODE_LEFT]) {
        	static_cast<Player*>(player2)->left();
      	}
      	if (keystate[SDL_SCANCODE_RIGHT]) {
        	static_cast<Player*>(player2)->right();
      	}
      	if (keystate[SDL_SCANCODE_UP]) {
       	 	static_cast<Player*>(player2)->up();
      	}
      	if (keystate[SDL_SCANCODE_DOWN]) {
        	static_cast<Player*>(player2)->down();
      	}
		if (keystate[SDL_SCANCODE_RCTRL]) {
        	static_cast<Player*>(player2)->Attack();
      	}
	  }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
return false;
}
