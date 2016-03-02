//
//  gamedata.h
//  CPSC-4160-Project-2
//
//  Created by Evan Dorn on 2/23/16.
//  Copyright © 2016 evandorn. All rights reserved.
//

#ifndef gamedata_h
#define gamedata_h

#include <string>
#include <map>

#include "vector2f.h"
#include "parseXML.h"

class Gamedata {
public:
    static Gamedata* getInstance();
    ~Gamedata();
    void displayData() const;
    
    bool getXmlBool(const std::string&) const;
    const std::string& getXmlStr(const std::string&) const;
    float getXmlFloat(const std::string&) const;
    int getXmlInt(const std::string&) const;
    float getRandInRange(int min, int max) const;
    float getRandFloat(float min, float max) const;
    
private:
    static Gamedata* instance;
    ParseXML parser;
    const map<std::string, std::string> gameData;
    
    Gamedata(const std::string& fn = "xmlSpec/game.xml");
    Gamedata(const Gamedata&);
    Gamedata& operator=(const Gamedata&);
};

#endif /* gamedata_h */
