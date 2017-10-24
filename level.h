#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>
#include <sstream>
#include "xmlhelper.h"

// pozycje kopii poziomu do renderowania
enum {
    LEVEL_COPY_MIDDLE_BOTTOM,
    LEVEL_COPY_LEFT_BOTTOM,
    LEVEL_COPY_LEFT_MIDDLE,
    LEVEL_COPY_LEFT_TOP,
    LEVEL_COPY_MIDDLE_TOP,
    LEVEL_COPY_RIGHT_TOP,
    LEVEL_COPY_RIGHT_MIDDLE,
    LEVEL_COPY_RIGHT_BOTTOM
};

class Level
{
    private:
        Uint32 startTime;

    public:
        Uint32 timeLimit;
        double r; // promień wszechświata
        Level();
        Level(double r);
        Level(double r, Uint32 timeLimit);
        Uint32 TimeLeft();
        std::string TimeLeftString();
        bool Serialize(std::ofstream& file);
        bool Deserialize(std::ifstream& file);
};

#endif // LEVEL_H
