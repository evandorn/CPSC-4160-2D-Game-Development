// Brian Malloy        Game Construction
#include "manager.h"
#include "frameFactory.h"
# include "gamedata.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

//IOManager*     IOManager::instance = NULL;  //Not needed for Meyers Signleton 
//Gamedata*      Gamedata::instance = NULL;
//FrameFactory*  FrameFactory::instance = NULL;


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
