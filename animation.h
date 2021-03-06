#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>
#include <tinyxml2.h>
#include "xmlhelper.h"

class Animation
{
    private:
        Uint8 currentFrame;
        Uint8 numberOfFrames; // liczba klatek
        Uint32 timeBetweenFrames; // w milisekundach
        Uint32 lastFrameTime;
        // wymiary pojedynczej klatki
        Uint32 width;
        Uint32 height;

    public:
        Animation();
        Animation(Uint8 numberOfFrames, Uint8 framesPerSecond, Uint32 width, Uint32 height);
        Uint8 Width();
        Uint8 Height();
        Uint8 CurrentFrame();
        bool Serialize(std::ofstream& file);
        bool Deserialize(std::ifstream& file);
        bool Serialize(tinyxml2::XMLDocument *xmlDoc, tinyxml2::XMLNode *root);
        bool Deserialize(tinyxml2::XMLNode* root);
};

#endif // ANIMATION_H
