#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    //initialize array of objPos with ARRAY_MAX_CAP capacity
    aList = new objPos[ARRAY_MAX_CAP];
    sizeArray = ARRAY_MAX_CAP;
    sizeList = 0;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return(sizeList);
}

void objPosArrayList::insertHead(objPos thisPos)
{
    //ensure list size never exceeds capacity of array
    if (sizeList >= sizeArray){
        return;
    }
    for (int i = sizeList; i>0;i--){
        //shuffle towards the tail
        aList[i].setObjPos(aList[i-1]);
    }
    aList[0].setObjPos(thisPos);
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    //append objPos object to end of arrayList
    aList[sizeList].setObjPos(thisPos);
    sizeList++;
}

void objPosArrayList::removeHead()
{
    objPos null_pos;
    aList[0].setObjPos(null_pos);

    //shuffle towards head
    for (int i = 0; i<sizeList;i++){
        aList[i].setObjPos(aList[i+1]);
    }
    sizeList--;
}

void objPosArrayList::removeTail()
{
    objPos null_pos;
    aList[sizeList].setObjPos(null_pos);
    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    //return object of arrayList from specified index
    returnPos.setObjPos(aList[index]);
}