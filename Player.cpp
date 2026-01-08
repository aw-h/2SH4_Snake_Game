#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    playerPosList = new objPosArrayList;
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos start(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*'); //this is the first part in the list
    playerPosList->insertHead(start);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList; //delete the array list from the heap
}

const objPosArrayList* Player::getPlayerPos() const //copies the coordinates of the player's head to the objPos returnPos
{
    return playerPosList; //return the reference to the entire list
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput(); //assigning to a variable makes it more readable within the code block

    if(input != 0)  // if not null character. Now, we are using the get input fn of the passed in GM class
    {
        switch(input)
        {                      
            case 27:  //escape char; exit
                mainGameMechsRef->setExitTrue(); //Pointer method of using fn to set exit flag to 1
                break;
            case 'w': //move 'up' or decrement y
                if (myDir != UP && myDir != DOWN) //AND; if either of these are true (UP for redundancy, and DOWN as the opposite direction), do not make the following change
                {
                    myDir = UP;
                }
                break;
            case 'a': //move 'left' or decrement x
                if (myDir != LEFT && myDir != RIGHT)
                {
                myDir = LEFT;
                }
                break;
            case 's': //move 'down' or increment y
                if (myDir != UP && myDir != DOWN)
                {
                myDir = DOWN;
                }
                break;
            case 'd': //move 'right' or increment x
                if (myDir != LEFT && myDir != RIGHT)
                {
                myDir = RIGHT;
                }
                break;
            default:
                break;
        }

        mainGameMechsRef->setInput(0); //once the input has been processed, whether useful or not, it should be reset
    }          
}

void Player::movePlayer()
{
    switch(myDir)
    {
        case(UP):
        {
            if (playerPosList->getHeadElement().pos->y - 1 == 0) //the head runs into border on the top
            {
                objPos newHead(playerPosList->getHeadElement().pos->x, mainGameMechsRef->getBoardSizeY() - 2, '*'); //make a new head. The x is the same as the previous head, the y is now wrapping to the bottom
                playerPosList->insertHead(newHead);
                playerPosList->removeTail(); //moved forward; remove tail
                //playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2; //manually move to bottom; size - 1 is the border, size - 2 is the first valid space
            }
            else
            {
                objPos newHead(playerPosList->getHeadElement().pos->x, playerPosList->getHeadElement().pos->y - 1, '*'); //make a new head. The x is the same as the previous head, the y is now wrapping to the bottom
                playerPosList->insertHead(newHead);
                playerPosList->removeTail(); //etc., tail removed
            }
            break;
        }
        case(LEFT):
        {
            if (playerPosList->getHeadElement().pos->x - 1 == 0) //etc. head runs into border on the left
            {
                objPos newHead(mainGameMechsRef->getBoardSizeX() - 2, playerPosList->getHeadElement().pos->y, '*'); //similar formula; y constant, x wraps around
                playerPosList->insertHead(newHead);
                playerPosList->removeTail(); //moved forward; remove tail
            }
            else
            {
                objPos newHead(playerPosList->getHeadElement().pos->x - 1, playerPosList->getHeadElement().pos->y, '*');
                playerPosList->insertHead(newHead);
                playerPosList->removeTail();
            }
            break;
        }
        case(DOWN):
        {
            if (playerPosList->getHeadElement().pos->y + 1 == mainGameMechsRef->getBoardSizeY() - 1) //ie in default case, 14, due to indexing from 0 to 14. This makes it adaptable to different board sizes
            {
                objPos newHead(playerPosList->getHeadElement().pos->x, 1, '*'); //x constant, y -> 1
                playerPosList->insertHead(newHead);
                playerPosList->removeTail(); 
                
                //playerPos.pos->y = 1; //manually move to the top. This coordinate is universally true for any game board size
            }
            else
            {
                objPos newHead(playerPosList->getHeadElement().pos->x, playerPosList->getHeadElement().pos->y + 1, '*'); 
                playerPosList->insertHead(newHead);
                playerPosList->removeTail(); 
            }
            break;
        }
        case(RIGHT):
        {
            if (playerPosList->getHeadElement().pos->x + 1 == mainGameMechsRef->getBoardSizeX() - 1) //in default case, 29 from [0, 29]
            {
                objPos newHead(1, playerPosList->getHeadElement().pos->y, '*'); //x -> 1, y constant
                playerPosList->insertHead(newHead);
                playerPosList->removeTail(); 
                
                //playerPos.pos->x = 1; //manually move to the left
            }
            else
            {
                objPos newHead(playerPosList->getHeadElement().pos->x + 1, playerPosList->getHeadElement().pos->y, '*'); //x -> 1, y constant
                playerPosList->insertHead(newHead);
                playerPosList->removeTail(); 
            }
            break;
        }
    }
}

void Player::updateLength(bool ateFood)
{
    if (ateFood) //only if food was eaten (normal food) will the snake increase in length
    {
        playerPosList->increaseLength();
    }
}