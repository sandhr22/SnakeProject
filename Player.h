#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib>

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* thisFoodRef);
        ~Player(); 

        objPosArrayList* getPlayerPos();
        void updatePlayerDir();
        void movePlayer();
        void updateMovement(objPos &currentHeadPos);

        bool checkFoodConsumption(objPos currentHeadPos, char &symbol);
        void changePlayerLength(objPos currentHeadPos, char symbol);
        char getPlayerDir();

    private:
        objPosArrayList *playerPosList;
            
        enum Dir myDir;

        GameMechs* mainGameMechsRef;

        Food *foodRef;
};

#endif