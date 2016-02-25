//
//  ioManager.h
//  CPSC-4160-Project-2
//
//  Created by Evan Dorn on 2/23/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#ifndef ioManager_h
#define ioManager_h

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <SDL_ttf/SDL_ttf.h>

#include <string>
#include <sstream>

#include "gamedata.h"

class IOManager {
public:
    static IOManager* getInstance();
    SDL_Surface * getScreen() const { return screen; }
    ~IOManager() {
        TTF_CloseFont(font);
    }
    SDL_Surface* loadAndSet(const std::string& filename,
                            bool setcolorkey) const;
    
    void printMessageAt(const std::string& msg, Sint16 x, Sint16 y) const;
    void printMessageCenteredAt(const std::string& msg, Sint16 y) const;
    void printStringAfterMessage(const std::string&,
                                 Uint32 x, Uint32 y) const;
    
    template <typename T>
    void printMessageValueAt(const std::string& msg, T value,
                             Sint16 x, Sint16 y) const;
    
    void buildString(SDL_Event);
    void clearString() { inputString = ""; }
    const std::string& getString() const { return inputString; }
private:
    IOManager();
    IOManager(const IOManager&);
    IOManager& operator=(const IOManager&);
    static IOManager* instance;
    const Gamedata* gdata;
    int viewWidth;
    int viewHeight;
    const unsigned MAX_STRING_SIZE;
    SDL_Surface * screen;
    TTF_Font *font;
    SDL_Color color;
    std::string inputString;
};

#endif /* ioManager_h */
