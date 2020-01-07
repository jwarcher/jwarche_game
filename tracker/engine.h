#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "world.h"
#include "viewport.h"
#include "clock.h"
#include "gameData.h"
#include "HUD.h"
#include "healthBar.h"
#include "sound.h"
#include <time.h>
#include <chrono>
#include <cmath>



class CollisionStrategy;
class SmartSprite;
class SubjectSprite;
class HealthBar;
class ShootingSprite;
class SDLSound;

class Engine {
public:
  Engine (bool);
  ~Engine ();
  bool play();
  void switchSprite();

private:
  Gamedata& gdata;
  const RenderContext& rc;
  const IoMod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World world;
  World world2;
  World world3;
  Viewport& viewport;

  SubjectSprite* player;
  SubjectSprite* player2;
  //SubjectSprite* deadPlayer;
  //SubjectSprite* deadPlayer2;
  std::vector<ShootingSprite*> ganon;
  std::vector<ShootingSprite*> deadGanon;
  //Ganon* ganon;
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;

  Hud& hud;
  bool collision;
  bool playerNum;
  bool playerNumCheck;
  bool Music;
  bool godMode;
  bool HitMarker;
  bool HitMarker2;
  std::chrono::time_point<std::chrono::system_clock> start;
  std::chrono::time_point<std::chrono::system_clock> start2;
  std::chrono::time_point<std::chrono::system_clock> end;
  std::chrono::time_point<std::chrono::system_clock> beginClock;
  HealthBar* healthBar;
  HealthBar* healthBar2;
  HealthBar* GanonHealth;
  SDLSound* BigFish;
  int currentSprite;
  bool hudFlag;
  bool makeVideo;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  void printScales() const;
  void checkForCollisions();
};
