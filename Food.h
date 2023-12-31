#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#define BUCKET_ITEMS 5

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Food
{
    private:
        objPosArrayList *foodBucket;
        GameMechs* mainGameMechsRef;

    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        objPosArrayList* getFoodPos();

        void generateFood(objPosArrayList &blockOff);

        void getFoodPos(objPosArrayList &returnPos);
};

#endif