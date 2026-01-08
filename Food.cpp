#include "Food.h"

Food::Food(GameMechs *thisGMRef, Player *thisPlayerRef, const objPosArrayList *playerALRef, objPosArrayList *foodALRef)
{   
    //something
    mainGameMechsRef = thisGMRef;
    mainPlayerRef = thisPlayerRef;
    playerArrayList = playerALRef; //pass in an objPos array list so it is known which coordinates are not valid/occupied
    foodArrayList = foodALRef; //
    
    generateFood(playerArrayList, foodArrayList);
}

Food::~Food() //is this necessary?
{

}

void Food::generateFood(const objPosArrayList* playerArrayList, objPosArrayList* foodArrayList) //both the body array lsit and the food bin array list are passed in separately as one is static sized, and one is dynamic
{
    int keepGoing = 1;
    
    while (keepGoing)
    {
        int isUnique = 1;

        foodPos.pos->x = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1; //rerun the same routine until a new unique coordinate pair is found
        foodPos.pos->y = rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1;

        for (int i = 0; i < playerArrayList->getSize(); i++) //check if this matches any of the coordinate pairs already in the array list. If so, regenerate
        {
            isUnique &= foodPos.pos->x != playerArrayList->getElement(i).pos->x && foodPos.pos->y != playerArrayList->getElement(i).pos->y; //check if this coordinate pair overlaps with any of the body segments
            if (not isUnique)
            {
                break;
            }
        } 
        for (int i = 0; i < foodArrayList->getSize(); i++) //check if this matches any of the coordinate pairs already in the array list. If so, regenerate
        {
            isUnique &= foodPos.pos->x != foodArrayList->getElement(i).pos->x && foodPos.pos->x != foodArrayList->getElement(i).pos->y; //check if this coordinate pair overlaps with any of the othe foods
            if (not isUnique)
            {
                break;
            }
        }
        
        if (isUnique) 
        {
            foodArrayList->insertHead(foodPos); //if unique, insert into food bin
            keepGoing = 0; //stop the while loop; unique coordinate pair found
        }
        else
        {
            keepGoing = 1; //the coordinate pair is not unique. Loop through again
        }
    }
    foodPos.symbol = 'f';
}

objPos Food::getFoodPos() const
{
    objPos copy; //make a copy with the coordinates and check
    copy.pos->x = foodPos.pos->x;
    copy.pos->y = foodPos.pos->y;
    copy.symbol = foodPos.symbol; //this is necessary in order to print the food character

    return copy;
}

void Food::addScore()
{
    mainGameMechsRef->incrementScore(1); //a normal fruit should only increment score by 1 point
}

void supFood::generateFood(const objPosArrayList* playerArrayList, objPosArrayList* foodArrayList) //overriding the default one
{
    int keepGoing = 1;
    
    while (keepGoing)
    {
        int isUnique = 1;

        foodPos.pos->x = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1; //rerun the same routine until a new unique coordinate pair is found
        foodPos.pos->y = rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1;

        for (int i = 0; i < playerArrayList->getSize(); i++) //check if this matches any of the coordinate pairs already in the array list. If so, regenerate
        {
            isUnique &= foodPos.pos->x != playerArrayList->getElement(i).pos->x && foodPos.pos->y != playerArrayList->getElement(i).pos->y; //check if this coordinate pair overlaps with any of the body segments
            if (not isUnique)
            {
                break;
            }
        } 

        for (int i = 0; i < foodArrayList->getSize(); i++) //check if this matches any of the coordinate pairs already in the array list. If so, regenerate
        {
            isUnique &= foodPos.pos->x != foodArrayList->getElement(i).pos->x && foodArrayList->getElement(i).pos->y; //check if this coordinate pair overlaps with any of the othe foods
            if (not isUnique)
            {
                break;
            }
        }
        
        if (isUnique) 
        {
            foodArrayList->insertHead(foodPos); //if unique, insert into food bin
            keepGoing = 0; //stop the while loop; unique coordinate pair found
        }
        else
        {
            keepGoing = 1; //the coordinate pair is not unique. Loop through again
        }
    }
    
    foodPos.symbol = 'F'; //unique symbol for super foods
}

void supFood::addScore()
{
    mainGameMechsRef->incrementScore(10); //a special fruit will increment score by 10 points
}