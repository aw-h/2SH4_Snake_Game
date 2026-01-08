#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 400 //given a 30 by 15 game board, there are (30 - 2) * (15 - 2) valid spaces = 364. 400 should be reasonably large enough to fit even the best of games

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList;
        int listSize;
        int arrayCapacity;

    public:
        objPosArrayList();
        ~objPosArrayList();

        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;
};

#endif