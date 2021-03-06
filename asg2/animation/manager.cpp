//
//  manager.cpp
//  CPSC-4160-Project-2
//
//  Created by Evan Dorn on 2/23/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "TwoWayMultiFrameSprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  world("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  stars("stars", Gamedata::getInstance().getXmlInt("stars/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(0),

  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
  sprites.push_back( new TwoWayMultiFrameSprite("samus") );
  sprites.push_back( new Sprite("metroidgaint") );
  sprites.push_back( new Sprite("metroidtiny") );
  viewport.setObjectToTrack(sprites[currentSprite]);
}

void Manager::draw() const {
  stars.draw();
  world.draw();
  for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }

  io.printMessageValueAt("Seconds: ", clock.getSeconds(), 10, 20);
  io.printMessageValueAt("fps: ", clock.getAvgFps(), 10, 40);
  io.printMessageAt("Press T to switch sprites", 10, 70);
  io.printMessageAt("Press 1, 2 to explode a sprite", 30, 100);
    /*
  io.printMessageAt("Press P to pause the animation", 10, 90);
     */
  io.printMessageAt(title, 10, 450);
  viewport.draw();

  SDL_Flip(screen);
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::switchSprite() {
  currentSprite = (currentSprite+1) % sprites.size();
  viewport.setObjectToTrack(sprites[currentSprite]);
}

void Manager::update() {
  ++clock;
  Uint32 ticks = clock.getElapsedTicks();

  static unsigned int lastSeconds = clock.getSeconds();
  if ( clock.getSeconds() - lastSeconds == 5 ) {
    lastSeconds = clock.getSeconds();
    //switchSprite();
  }

  for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
  }
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  stars.update();
  world.update();
  viewport.update(); // always update viewport last
}

void Manager::play() {
  SDL_Event event;
  bool done = false;
  bool keyPressed = false;

  while ( not done ) {
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
        if(event.type == SDL_KEYUP) {
            keyPressed = false;
        }

      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }
        
        if (keystate[SDLK_t]) {
          switchSprite();
        }
        if (keystate[SDLK_s]) {
          clock.toggleSloMo();
        }
        if (keystate[SDLK_1]) {
              sprites[1]->explode();
        }
        if (keystate[SDLK_2]) {
            sprites[2]->explode();
        }
          
        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
          if (keystate[SDLK_p] && !keyPressed) {
              keyPressed = true;
              if ( clock.isPaused() ) clock.unpause();
              else clock.pause();
          }
      }
    }
    draw();
    update();
  }
}
