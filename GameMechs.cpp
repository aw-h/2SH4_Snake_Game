#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false; //set both to false initially
    winFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    winFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    
bool GameMechs::getWinFlagStatus() const
{
    return winFlag;
}

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore(int amt)
{
    score += amt; //This now accounts for the above and beyond feature; we can now specify the score added within the subclasses
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true; //when the player stops playing in general. Further specificity such as the loseFlag is possible
}

void GameMechs::setLoseFlag()
{
    loseFlag = true; //when the player loses specifically, ie crashes into themselves
    exitFlag = true; //the game also stops
}

void GameMechs::setWinFlag()
{
    winFlag = true; //player wins
    exitFlag = true; //the game also stops
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here