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
objPos* playerData; //testing; used to store the coordinates and symbol of the player as an objPos is to be passed into the getPlayerPos fn. I don't think we need this anymore
Food** foodBin; //bin for the food objects
//Food** foodBin; //pointer to food bin on the heap. Must be double pointer as each needs to be a pointer (pass by pointer) to allow polymorphism
objPosArrayList* playerALPtr; //pointer to the coordinate pairs for the snake segments
objPosArrayList* foodALPtr; //stores the coordinates for the food segments

int main(void)
{

    Initialize();

    while(gmPtr->getExitFlagStatus() == false) //only run if 
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

    gmPtr = new GameMechs(3,9);
    playerPtr = new Player(gmPtr);
    //playerData = new objPos; //is this needed anymore?
    playerALPtr = new objPosArrayList(); //is this needed anymore?
    foodALPtr = new objPosArrayList; //this seems quite wasteful (400 spots...) maybe change this

    
    foodBin = new Food*[foodBinSize]; //allocate 5 Foods on the heap
    for (int i = 0; i < foodBinSize - 1; i++) //generate the food items
    {
        foodBin[i] = new Food(gmPtr, playerPtr->getPlayerPos(), foodALPtr);
        foodBin[i]->generateFood(playerPtr->getPlayerPos(), foodALPtr);
    }
    foodBin[4] = new supFood(gmPtr, playerPtr->getPlayerPos(), foodALPtr); //the last food item, the 5th, is a super food
    foodBin[4]->generateFood(playerPtr->getPlayerPos(), foodALPtr);
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
    playerPtr->updatePlayerDir();
    playerPtr->movePlayer();
    bool ateFood = false; //check if the snake has eaten food. If so, do the necessary logic with the lengthening it

    for (int i = 0; i < foodBinSize; i++)
    {
        if (playerPtr->getPlayerPos()->getHeadElement().pos->x == foodALPtr->getElement(i).pos->x && playerPtr->getPlayerPos()->getHeadElement().pos->y == foodALPtr->getElement(i).pos->y) //the head
        {
            foodBin[i]->addScore(); //this is polymorphic; if its the correct food, it will add 10 instead of 1
            
            if (i <= 3) //if the eaten food is one of the normal ones (ie index 0 - 3), replace with a normal food
            {
                foodBin[i]->regenerateFood(playerALPtr, foodALPtr, i);
                ateFood = true; //food has been eaten. This is only "true" if it's a normal food; super food does not increase length
                break;
            }
            else
            {
                foodBin[i]->regenerateFood(playerALPtr, foodALPtr, i);
                break;
            }
        }
    }

    playerPtr->updateLength(ateFood);

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
    MacUILib_clearScreen();    

    // playerPtr->getPlayerPos(*playerData); //update the player's coordinates. Might not need to do anymore sicne it is done in RunLogic

    for (int i = 0; i < gmPtr->getBoardSizeY(); i++) //length 10; # of rows. y values
    {        
        for (int j = 0; j < gmPtr->getBoardSizeX(); j++) //width 20; # of chars per row. x values
        {
            if (i == 0 || i == gmPtr->getBoardSizeY() - 1) //top/bottom edges (0 or 9, in the default case); 20 #'s
            {
                MacUILib_printf("#");
                continue; //iterate next loop;
            }   
            else if (j == 0 || j == gmPtr->getBoardSizeX() - 1) //left/right edges (0 -r 19 in the default case)
            {
                MacUILib_printf("#");
                continue;
            }
            else //the else case is quite different than before; it will capture a snake body segment, a food item, or a blank ' ', as it is necessary to loop through every body/food coordinate to see if they match
            {
                int somethingPrinted = 0; //check if either a snake segment/food item has been printed. If not, print a ' '
                for (int k = 0; k < playerPtr->getPlayerPos()->getSize(); k++)
                    //playerALPtr->getSize(); k++) //go through the entire length of the snake; see if any coordinates match
                {
                    if (i == playerPtr->getPlayerPos()->getElement(k).pos->y && j == playerPtr->getPlayerPos()->getElement(k).pos->x)
                        //playerALPtr->getElement(k).pos->y && j == playerALPtr->getElement(k).pos->x) //spot is occupied by snake segment
                    {
                        MacUILib_printf("%c", playerPtr->getPlayerPos()->getElement(k).symbol);
                            //playerPtr->getPlayerPos()->getElement(k).symbol);
                        somethingPrinted = 1;
                    }
                }
                for (int k = 0; k < foodBinSize; k++)
                {
                    if (i == foodALPtr->getElement(k).pos->y && j == foodALPtr->getElement(k).pos->x) //spot is occupied by food item
                    {
                        MacUILib_printf("%c", foodBin[k]->getFoodPos().symbol);
                        somethingPrinted = 1;
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
    MacUILib_printf("Welcome to Andrew's and Anushka's Snake Game! Press ESC to leave.\nScore: %d\n", gmPtr->getScore());
    MacUILib_printf("~DEBUG MESSAGES~\n");
    MacUILib_printf("Snake size: %d\n", playerPtr->getPlayerPos()->getSize());
    gmPtr->getExitFlagStatus() ? MacUILib_printf("exitFlag: true\n") : MacUILib_printf("exitFlag: false\n"); //ternary debugging statements
    gmPtr->getLoseFlagStatus() ? MacUILib_printf("loseFlag: true\n") : MacUILib_printf("loseFlag: false\n"); 
    int xSize = gmPtr->getBoardSizeX();
    int ySize = gmPtr->getBoardSizeY();
    int validSpaces = (xSize - 2) * (ySize - 2) - 5; 
    MacUILib_printf("Valid spaces: %d\n", validSpaces);

    if (gmPtr->getExitFlagStatus()) //if exitFlag is true, start preparing to exit the program
    {
        if (gmPtr->getLoseFlagStatus()) //further condition; if the player is leaving specifically because they lost, display this message instead
        {
            MacUILib_printf("You lost. Thanks for playing!\n"); //should this be in cleanup instead? ie cleaning up to put the final statement, which is this
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
    //delete playerData;
    delete playerALPtr;
    delete foodALPtr;
    for (int i = 0 ; i < foodBinSize; i++)
    {
        delete foodBin[i]; //each fruit itself is on the heap. Delete it
    }
    delete[] foodBin; //delete the entire foodBin


    MacUILib_uninit();
}
