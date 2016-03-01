//
//  clock.h
//  CPSC-4160-Project-2
//
//  Created by Evan Dorn on 2/23/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#ifndef clock_h
#define clock_h

#include <SDL/SDL.h>
#include <string>
#include <deque>

class Manager;

class Clock {
public:
    static Clock& getInstance();
    unsigned int getTicks() const;
    unsigned int getTotalTicks() const { return sumOfAllTicks; }
    
private:
    friend class Manager;
    
    bool started;
    bool sloMo;
    const bool framesAreCapped;
    const int frameCap;
    bool paused;
    
    unsigned int frames;
    std::deque<int> recentFrames;
    const unsigned int maxFramesToAvg;
    
    unsigned int tickSum;
    unsigned int sumOfAllTicks;
    unsigned int timeAtStart;
    unsigned int timeWhenPaused;
    unsigned int currTicks;
    unsigned int prevTicks;
    unsigned int ticks;
    
    unsigned int getElapsedTicks();
    Clock& operator++();
    void toggleSloMo();
    
    bool isPaused() const  { return paused; }
    bool isStarted() const { return started; }
    unsigned int getFrames() const  { return frames;  }
    unsigned int getSeconds() const { return getTicks()/1000;  }
    unsigned int capFrameRate() const;
    int getFps() const;
    int getAvgFps() const;
    
    void start();
    void pause();
    void unpause();
    void display() const;
    
    Clock();
    Clock(const Clock&);
    Clock&operator=(const Clock&);
};

#endif /* clock_h */
