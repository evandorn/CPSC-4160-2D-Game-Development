#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"

Clock& Clock::getInstance() {
  if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    throw std::string("Must init SDL before Clock");
  }
  static Clock clock; 
  return clock;
}

Clock::Clock() :
  started(false), 
  paused(false),
  sloMo(false), 
  framesAreCapped(Gamedata::getInstance().getXmlBool("framesAreCapped")), //Changed -> to . for Meyers
  frameCap(Gamedata::getInstance().getXmlInt("frameCap")), 
  frames(0), 
  recentFrames(),
  maxFramesToAvg(100),
  tickSum(0),
  sumOfAllTicks(0),
  timeAtStart(0),
  timeAtPaused(0), 
  currTicks(0), prevTicks(0), ticks(0) 
 
  {
  start();
}

Clock::Clock(const Clock& c) :
  started(c.started), 
  paused(c.paused),
  sloMo(c.sloMo), 
  framesAreCapped(c.framesAreCapped), 
  frameCap(c.frameCap), 
  frames(c.frames), recentFrames(c.recentFrames), 
  maxFramesToAvg(c.maxFramesToAvg), tickSum(c.tickSum),
  sumOfAllTicks(c.sumOfAllTicks),
  timeAtStart(c.timeAtStart), timeAtPaused(c.timeAtPaused),
  currTicks(c.currTicks), prevTicks(c.prevTicks), ticks(c.ticks) 


  {
  start();
}


void Clock::display() const { 
  static unsigned int lastFrames = 0;
  static unsigned int oldFrames = 0;
  static unsigned int seconds = getSeconds();

  if ( getSeconds() > seconds ) {
    seconds = getSeconds();
    lastFrames = frames - oldFrames;
    oldFrames = frames;
  }
  IOManager::getInstance(). //Change from -> to . for Meyers Singleton 
    printMessageValueAt("seconds: ", seconds, 10, 30);
  IOManager::getInstance().
    printMessageValueAt("frames in sec: ", lastFrames, 10, 50);
}

void Clock::toggleSloMo() {
  if( started && !sloMo ) {
    sloMo = true;
  }
  else if ( started && sloMo ) {
    timeAtStart = SDL_GetTicks();
    sloMo = false;
  }
}

unsigned int Clock::getTicks() const { 
  if ( sloMo ) return 1;
  else return SDL_GetTicks() - timeAtStart; 
}

unsigned int Clock::getElapsedTicks() { 
  if (paused) {return 0;}
  if ( sloMo ) {return 1;}

  currTicks = getTicks();
  ticks = currTicks-prevTicks;
  unsigned int delay = capFrameRate();
  prevTicks = currTicks + delay;
  ticks += delay;
  sumOfAllTicks += ticks;
  return ticks;
}


unsigned int Clock::capFrameRate() const { 
  if ( !framesAreCapped ) return 0u;
  unsigned int delay = std::max(0.0,1000.0/frameCap+0.5 - ticks);
  SDL_Delay( delay );
  return delay;
}

int Clock::getFps() const { 
  if ( getSeconds() > 0 ) return frames/getSeconds();  
  else if ( getTicks() > 5000 and getFrames() == 0 ) {
    throw std::string("Can't getFps if you don't increment the frames");
  }
  else return 0;
}

int Clock::getAvgFps() const { 
  if ( getSeconds() > 0 && recentFrames.size() > maxFramesToAvg/2) {
    return recentFrames.size()/(tickSum/1000.0);  
  }
  if ( getTicks() > 5000 and getFrames() == 0 ) {
    throw std::string("Can't getFps if you don't increment the frames");
  }
  return 0;
}

Clock& Clock::operator++() { 
  if(!paused){
  ++frames; 
  if ( recentFrames.size() >= maxFramesToAvg ) { 
    tickSum -= recentFrames.front();
    recentFrames.pop_front(); 
  }
  recentFrames.push_back( ticks );
  tickSum += ticks;
}
  return *this;
} 


void Clock::start() { 
  started = true; 
  paused = false; 
  frames = 0;
  timeAtPaused = timeAtStart = SDL_GetTicks(); 
}

void Clock::pause() {
  if( started && !paused ) {
    timeAtPaused = SDL_GetTicks() - timeAtStart; 
    paused = true; 
  }
}
void Clock::unpause() {
  if( started && paused ) {
    timeAtStart = SDL_GetTicks() - timeAtPaused;
    paused = false;
  }
}
