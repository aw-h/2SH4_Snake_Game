#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        bool winFlag; //when the player wins ie all spaces filled by either the snake, the foods, or the border
        int score;

        int boardSizeX;
        int boardSizeY;

        objPos food;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();
        bool getWinFlagStatus() const;
        void setWinFlag();

        char getInput() const;
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        void incrementScore(int amt); 
        
        // More methods should be added here
};

#endif