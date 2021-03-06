#include <string>
#include <iostream>
#include <ctime>
#include "sound.h"
using std::string;

SDLSound::~SDLSound() {
  std::cout << "Cleaning up sounds ..." << std::endl;
  std::clock_t start = std::clock();
  Mix_HaltMusic();
  Mix_FreeMusic(music);
  Mix_FreeMusic(music2);
  Mix_FreeMusic(music3);
  Mix_FreeMusic(music4);
  for (unsigned int i = 0; i < sounds.size(); ++i) {
    Mix_FreeChunk(sounds[i]);
  }
  Mix_CloseAudio();
  std::clock_t duration = std::clock() - start;
  std::cout << "Clean up took " << duration << " ticks\n";
}

SDLSound::SDLSound() : 
  volume(SDL_MIX_MAXVOLUME), 
  currentSound(-1), 
  music(NULL),
  music2(NULL),
  music3(NULL),
  music4(NULL),
  audioRate(22050), 
  audioChannels(2), 
  audioBuffers(4096),
  sounds(),
  channels() 
{

  if(Mix_OpenAudio(audioRate, MIX_DEFAULT_FORMAT, audioChannels, 
                   audioBuffers)){
    throw string("Unable to open audio!");
  }
  music = Mix_LoadMUS("sound/MaBoyVince.mp3");
  music2 = Mix_LoadMUS("sound/Moon.mp3");
  music3 = Mix_LoadMUS("sound/BP.mp3");
  music4 = Mix_LoadMUS("sound/FF7.mp3");
  // Need to install midi to play the following:
  // music = Mix_LoadMUS("sound/ballad2.mid");
  if (!music) throw string("Couldn't load 100Years.mp3")+Mix_GetError();

  startMusic();

  sounds.push_back( Mix_LoadWAV("sound/Boom.wav") );
  sounds.push_back( Mix_LoadWAV("sound/Gun.wav") );
  sounds.push_back( Mix_LoadWAV("sound/Thump.wav") );
  sounds.push_back( Mix_LoadWAV("sound/phaser.wav") );
  sounds.push_back( Mix_LoadWAV("sound/Putt1.wav") );
  sounds.push_back( Mix_LoadWAV("sound/explosion.wav") );
  sounds.push_back( Mix_LoadWAV("sound/cannon.wav") );
  sounds.push_back( Mix_LoadWAV("sound/Larc.wav") );
  for (unsigned int i = 0; i < sounds.size(); ++i) channels.push_back(i);
  std::cout << "Music and Sound is loaded" << std::endl;
}

void SDLSound::toggleMusic() {
  if( Mix_PausedMusic() ) { 
    Mix_ResumeMusic(); 
  } 
  else { 
    Mix_PauseMusic(); 
  } 
}

void SDLSound::operator[](int index) {
  if (currentSound >= 0) Mix_HaltChannel(currentSound);
  currentSound = index;
  Mix_VolumeChunk(sounds[index], volume);
  channels[index] = 
     Mix_PlayChannel(-1, sounds[index], 0);
}

void SDLSound::startMusic() {
  Mix_VolumeMusic(volume);
  Mix_PlayMusic(music, 1);
}

void SDLSound::stopMusic() {
  Mix_HaltMusic();
  //Mix_FreeMusic(music);
}

void SDLSound::startMusic2() {
  Mix_VolumeMusic(volume);
  Mix_PlayMusic(music2, 1);
}

void SDLSound::stopMusic2() {
  Mix_HaltMusic();
  //Mix_FreeMusic(music2);
}

void SDLSound::startMusic3() {
  Mix_VolumeMusic(volume);
  Mix_PlayMusic(music3, 1);
}

void SDLSound::stopMusic3() {
  Mix_HaltMusic();
  //Mix_FreeMusic(music3);
}

void SDLSound::startMusic4() {
  Mix_VolumeMusic(volume);
  Mix_PlayMusic(music4, 1);
}

void SDLSound::stopMusic4() {
  Mix_HaltMusic();
 // Mix_FreeMusic(music4);
}
