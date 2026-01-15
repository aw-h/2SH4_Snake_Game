#include <iostream>
#include <time.h>
#include <cstdlib>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
#define foodBinSize 5 //for above and beyond; define the bin size which contains all 5 foods

//bool exitFlag; //no longer needed as now we are using the exitFlag from GM

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

Player* playerPtr; //testing Iteration 1/needed onwards
GameMechs* gmPtr; //testing Iteration 1/needed onwards
Food** foodBin; //bin for the food objects
objPosArrayList* foodALPtr; //stores the coordinates for the food segments

int main(void)
{

    Initialize();

    while(gmPtr->getExitFlagStatus() == false) //only run if the game should not exit
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    srand(time(NULL)); //seed the rng using the current time

    gmPtr = new GameMechs();
    playerPtr = new Player(gmPtr);
    foodALPtr = new objPosArrayList(foodBinSize); //this seems quite wasteful (400 spots...) maybe change this

    
    foodBin = new Food*[foodBinSize]; //allocate 5 Foods on the heap
    for (int i = 0; i < foodBinSize - 1; i++) //generate the food items
    {
        foodBin[i] = new Food(gmPtr, playerPtr->getPlayerPos(), foodALPtr);
    }
    foodBin[4] = new supFood(gmPtr, playerPtr->getPlayerPos(), foodALPtr); //the last food item, the 5th, is a super food
    MacUILib_printf("Hi\n");
    foodBin[4]->generateFood(playerPtr->getPlayerPos(), foodALPtr); //generate the food using dynamic binding; otherwise the superfood constructor just calls the base food constructor
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        gmPtr->setInput(MacUILib_getChar()); //set the input in the game mechanics
    }
}

void RunLogic(void)
{
    MacUILib_clearScreen();
    playerPtr->updatePlayerDir();
    playerPtr->movePlayer();
    bool ateFood = false; //check if the snake has eaten food. If so, do the necessary logic with the lengthening it

    for (int i = 0; i < foodBinSize; i++)
    {
        if (playerPtr->getPlayerPos()->getHeadElement().pos->x == foodALPtr->getElement(i).pos->x && playerPtr->getPlayerPos()->getHeadElement().pos->y == foodALPtr->getElement(i).pos->y) //the head
        {
            foodBin[i]->addScore(); //this is polymorphic; if it's the correct food, it will add 10 instead of 1
            
            if (i <= 3) //if the eaten food is one of the normal ones (ie index 0 - 3), replace with a normal food
            {
                ateFood = true; //food has been eaten. This is only "true" if it's a normal food; super food does not increase length
                playerPtr->updateLength(ateFood);
                foodBin[i]->regenerateFood(playerPtr->getPlayerPos(), foodALPtr, i); //causing problems
                break;
            }
            else
            {
                foodBin[i]->regenerateFood(playerPtr->getPlayerPos(), foodALPtr, i); //causing problems?
                break;
            }
        }
    }


    for (int i = 1; i < playerPtr->getPlayerPos()->getSize(); i++) //compare the head's position to that of every other body segment, ie start at i = 1
    {
        if (playerPtr->getPlayerPos()->getHeadElement().pos->x == playerPtr->getPlayerPos()->getElement(i).pos->x && playerPtr->getPlayerPos()->getHeadElement().pos->y == playerPtr->getPlayerPos()->getElement(i).pos->y)
        {
            gmPtr->setLoseFlag();
        }
    }

    int xSize = gmPtr->getBoardSizeX();
    int ySize = gmPtr->getBoardSizeY();
    int validSpaces = (xSize - 2) * (ySize - 2) - 5; //this is the total number of spaces the snake can possibly take up; (x without borders) * (y without bordesr) - 5 for the 5 foods
    
    if (playerPtr->getPlayerPos()->getSize() == validSpaces) //all spaces are taken up; the player has won
    {
        gmPtr->setWinFlag();
    }
}

void DrawScreen(void)
{
    //MacUILib_clearScreen();    

    for (int i = 0; i < gmPtr->getBoardSizeY(); i++) //length 15; # of rows. y values
    {        
        for (int j = 0; j < gmPtr->getBoardSizeX(); j++) //width 30; # of chars per row. x values
        {
            if (i == 0 || i == gmPtr->getBoardSizeY() - 1) //top/bottom edges (0 or 14, in the default case); 20 #'s
            {
                MacUILib_printf("#");
                continue; //iterate next loop;
            }   
            else if (j == 0 || j == gmPtr->getBoardSizeX() - 1) //left/right edges (0 or 29 in the default case)
            {
                MacUILib_printf("#");
                continue;
            }
            else //the else case will capture a snake body segment, a food item, or a blank ' ', as it is necessary to loop through every body/food coordinate to see if they match
            {
                bool somethingPrinted = false; //check if either a snake segment/food item has been printed. If not, print a ' '
                for (int k = 0; k < playerPtr->getPlayerPos()->getSize(); k++)
                {
                    if (i == playerPtr->getPlayerPos()->getElement(k).pos->y && j == playerPtr->getPlayerPos()->getElement(k).pos->x)
                    {
                        if (k != 0 && playerPtr->getPlayerPos()->getHeadElement().pos->x == playerPtr->getPlayerPos()->getElement(k).pos->x && playerPtr->getPlayerPos()->getHeadElement().pos->y == playerPtr->getPlayerPos()->getElement(k).pos->y) //this condition is checking if the body segment is overlapping the head element. This will only occur if a crash has occured, so right before losing the game
                        {
                            continue;
                        }
                        else
                        {
                            MacUILib_printf("%c", playerPtr->getPlayerPos()->getElement(k).symbol);
                            somethingPrinted = true;
                        }
                    }
                }
                for (int k = 0; k < foodBinSize; k++)
                {
                    if (i == foodALPtr->getElement(k).pos->y && j == foodALPtr->getElement(k).pos->x) //spot is occupied by food item
                    {
                        MacUILib_printf("%c", foodBin[k]->getFoodPos().symbol);
                        somethingPrinted = true;
                    }
                }
                if (not somethingPrinted)
                {
                    MacUILib_printf(" "); //in the case that neither a snake segment nor a food item is printed, it is simply ' '
                }
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("\n");
    MacUILib_printf("Welcome to Andrew's rendition of the C++ Snake Game! Press ESC to leave.\nScore: %d\n", gmPtr->getScore());
    MacUILib_printf("~DEBUG MESSAGES~\n");
    MacUILib_printf("Snake size: %d\n", playerPtr->getPlayerPos()->getSize());
    gmPtr->getExitFlagStatus() ? MacUILib_printf("exitFlag: true\n") : MacUILib_printf("exitFlag: false\n"); //ternary debugging statements
    gmPtr->getLoseFlagStatus() ? MacUILib_printf("loseFlag: true\n") : MacUILib_printf("loseFlag: false\n"); 
    MacUILib_printf("Valid spaces: %d\n", (gmPtr->getBoardSizeX() - 2) * (gmPtr->getBoardSizeY() - 2) - playerPtr->getPlayerPos()->getSize() - 5);

    if (gmPtr->getExitFlagStatus()) //if exitFlag is true, start preparing to exit the program
    {
        if (gmPtr->getLoseFlagStatus()) //further condition; if the player is leaving specifically because they lost, display this message instead
        {
            MacUILib_printf("You lost. Thanks for playing!\n");
        }
        else if (gmPtr->getWinFlagStatus())
        {
            MacUILib_printf("Wow, you actually won! Congratulations, thanks for playing!");
        }
        else
        {
            MacUILib_printf("You are leaving without winning.\n");
        }
    }
}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay.
}


void CleanUp(void)
{
    // MacUILib_clearScreen(); //this leads to clearing the screen after the game over message is shown. Do not clear screen again
    
    delete playerPtr;
    delete gmPtr;
    delete foodALPtr;
    for (int i = 0 ; i < foodBinSize; i++)
    {
        delete foodBin[i]; //each fruit itself is on the heap; delete each instance
    }
    delete[] foodBin; //delete the entire foodBin


    MacUILib_uninit();
}
