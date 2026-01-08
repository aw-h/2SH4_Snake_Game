#ifndef FOOD_H //if not already defined, define the Food header file
#define FOOD_H

#define foodBinSize 5

#include <cstdlib>
#include "GameMechs.h"
#include "objPos.h"
#include "Player.h" //this is needed to keep track of player position
#include "objPosArrayList.h"


class Food
{
    protected: //these items should be protected (not private) as the subclasses (ie superfoods) will be using these
        GameMechs* mainGameMechsRef; //all subclasses should be able to work with GameMechs
        objPos foodPos; //holds position of generated food item
        // objPos dataPos; //captures the player's position initally (as just the head) to generate the first set of fruits
        Player* mainPlayerRef; //all subclasses should be aware of the player's coordinates
        const objPosArrayList* playerArrayList; //this should keep track of all relevant coordinates of ONLY the snake body
        objPosArrayList* foodArrayList; //similarly, this keeps track of all the relevant coordintaes of ONLY the fruits
    public: 
        Food(GameMechs *thisGMRef, const objPosArrayList *playerALRef, objPosArrayList *foodALRef); //default constructor. Same thing as the Player class, must have a reference of GameMechs
        ~Food(); //destructor. Is this needed?
        virtual void generateFood(const objPosArrayList* coordArrayList, objPosArrayList* foodArrayList); //generates a random food item such that it does not overlap on the player's (or any other fruit's) position. Virtual because this should be able to handle noraml and special fruit
        virtual void regenerateFood(const objPosArrayList* coordArrayList, objPosArrayList* foodArrayList, const int index); //regenerates a random food item of the same type once it is eaten
        objPos getFoodPos() const;
        virtual void addScore();
};

class supFood : public Food //superfood. Special things should happen if this is eaten
{
    public: 
        supFood(GameMechs *thisGMRef, const objPosArrayList *playerALRef, objPosArrayList *foodALRef) : Food(thisGMRef, playerALRef, foodALRef) {} //supFood's own constructor calls the base class' constructor. 
        ~supFood(); //destructor. Is this needed?
        void generateFood(const objPosArrayList* coordArrayList, objPosArrayList* foodArrayList); //generates a random food item such that it does not overlap on the player's (or any other fruit's) position. Virtual because this should be able to handle normal and special fruit
        void regenerateFood(const objPosArrayList* coordArrayList, objPosArrayList* foodArrayList, const int index); //regenerates a random food item of the same type once it is eaten
        void addScore();
};

#endif