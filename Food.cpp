#include "Food.h"


Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;

    //insert 5 food objects into the game board
    objPos startPos;
    foodBucket = new objPosArrayList();
    for(int i = 0; i < BUCKET_ITEMS; i++)
    {
        startPos.setObjPos(i, i,'O');
        foodBucket->insertHead(startPos);
    }

    //seed the RNG when Food object initialized
    srand(time(NULL));
}

Food::~Food()
{
    delete foodBucket;
    // Destructor that deletes the foodBucket Array list from the heap
}

objPosArrayList* Food::getFoodPos()
{
    return foodBucket;
    // return the reference to the playerPos array list
}

void Food::generateFood(objPosArrayList &blockOff)
{
    objPos bodySeg, foodObj[BUCKET_ITEMS];
    bool foodGeneratedFlag = false;
    char symbol = 'O';
    int candidateX = 0, candidateY = 0, xRange, yRange;

    xRange = mainGameMechsRef->getBoardSizeX() - 1;
    yRange = mainGameMechsRef->getBoardSizeY() - 1;

    //generate new positions for all food objects
    for(int items = 0; items < BUCKET_ITEMS; items++)
    {
        candidateX = 0;
        candidateY = 0;
        foodGeneratedFlag = false;

        //last generated food object is assigned '?' symbol
        if(items == BUCKET_ITEMS - 1)
            symbol = '?';

        //continue generating new food object data members until it passes all conditions to replace old object
        while(!foodGeneratedFlag)
        {
        
            foodGeneratedFlag = true;
            
            while(candidateX == 0)
            {
                candidateX = rand() % xRange;
            }

            while(candidateY == 0)
            {
                candidateY = rand() % yRange;
            }

            foodObj[items].setObjPos(candidateX, candidateY, symbol);
            
            //check that new generated food does not match another food object
            for(int k = 0; k < items; k++)
            {
                foodBucket->getElement(foodObj[k], k);
                if(foodObj[items].isPosEqual(foodObj+k))
                {
                    foodGeneratedFlag = false;
                    candidateX = 0;
                    candidateY = 0;
                    break;
                }
            }

            //check that generated food object does not overlap with player arrayList
            if(foodGeneratedFlag)
            {
                for(int i = 0; i < blockOff.getSize(); i++)
                {
                    blockOff.getElement(bodySeg, i);
                    if(foodObj[items].isPosEqual(&bodySeg))
                    {
                    foodGeneratedFlag = false;
                    candidateX = 0;
                    break;
                    } 
                }
            }
            
        }
        //remove old food objects and add in newly generated food objects
        foodBucket->removeTail();
        foodBucket->insertHead(foodObj[items]);
    }
}

void Food::getFoodPos(objPosArrayList &returnPos)
{
    //returnPos receives food arrayList, foodBucket
    returnPos = *foodBucket;
}