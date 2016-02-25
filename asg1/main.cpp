//
//  Main.cpp
//  CPSC416-Project1-SDLAnimation
//
//  Created by Evan Dorn on 2/9/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#include <SDL.h>
#include <iostream>
#include <string>

#include "Manager.h"
#include "Sprite.h"
#include "generateFrames.h"

int main(int, char*[]) {
  try {
      Manager appManager;
      appManager.init();
      appManager.play();
  }
  catch(const std::string& msg) { std::cout << msg << std::endl;  }
  catch(...) { std::cout << "oops" << std::endl;  }
    
    return 0;
}
