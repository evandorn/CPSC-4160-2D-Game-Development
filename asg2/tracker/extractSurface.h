//
//  extractSurface.h
//  CPSC-4160-Project-2
//
//  Created by Evan Dorn on 2/23/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#ifndef extractSurface_h
#define extractSurface_h

#include <SDL/SDL.h>

class ExtractSurface {
public:
    static ExtractSurface& getInstance();
    SDL_Surface* get(SDL_Surface*, int, int, int, int) const;
private:
    Uint32 getpixel(SDL_Surface*, int, int) const;
    void putpixel(SDL_Surface *, int, int, Uint32) const;
};

#endif /* extractSurface_h */
