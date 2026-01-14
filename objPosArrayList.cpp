#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; //pointer to array of objPos, 
    arrayCapacity = ARRAY_MAX_CAP; //use given variable names
    listSize = 0;
}

objPosArrayList::objPosArrayList(int size)
{
    aList = new objPos[size];
    arrayCapacity = size;
    listSize = 0;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; //delete entire list

    arrayCapacity = 0; //optional destructor commands
    listSize = 0;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    for (int i = listSize; i > 0; i--) //move index i - 1 to i. Thus, go up to index 1.
    {
        aList[i] = aList[i - 1]; //shift all elements forward such that there is now room to insert a new head
    }
    aList[0] = thisPos; //now that all the elements are shifted, insert head

    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    aList[listSize++] = thisPos; //an element has been added. Increase listSize afterwards
}

void objPosArrayList::updateElement(const int index, objPos newPos)
{
    aList[index].pos->x = newPos.pos->x;
    aList[index].pos->y = newPos.pos->y;
    aList[index].symbol = newPos.symbol;
}

void objPosArrayList::removeHead()
{
    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1]; //overwrite the head value, then remove access to the last index
    }    
    listSize--;
}

void objPosArrayList::removeTail()
{
    listSize--; //make the last index out of access; "lazy deletion"
}

void objPosArrayList::increaseLength()
{
    listSize++; //since all deletion is lazy, you can simply add back the removed final element
}

objPos objPosArrayList::getHeadElement() const
{
    objPos copy; //make a copy of the objPos element at the first index and returns it
    copy.setObjPos(aList[0]); //copy now has the same values as the elements of the first objPos

    return copy;
}

objPos objPosArrayList::getTailElement() const
{
    objPos copy; //make a copy of the objPos element at the last meaningful index and return it
    copy.setObjPos(aList[listSize - 1]); //copy now has the same values as the elements of the last objPos

    return copy;
}

objPos objPosArrayList::getElement(int index) const
{
    objPos copy; //make a copy of the objPos element at index "index" and return it
    copy.setObjPos(aList[index]); //copy now has the same values as the elements of the "indexth" objPos

    return copy;
}