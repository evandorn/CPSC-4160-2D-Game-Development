//
//  main.cpp
//  CPSC-4160-Project-2
//
//  Created by Evan Dorn on 2/23/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#include "manager.h"
#include "frameFactory.h"

IOManager*     IOManager::instance = NULL;
Gamedata*      Gamedata::instance = NULL;
FrameFactory*  FrameFactory::instance = NULL;

int main(int, char*[]) {
    try {
        Manager manager;
        manager.play();
    }
    catch (const std::string& msg) { std::cout << msg << std::endl; }
    catch (...) {
        std::cout << "Oops, someone threw an exception!" << std::endl;
    }
    return 0;
}
