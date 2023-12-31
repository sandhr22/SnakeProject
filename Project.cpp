#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

//declare global object pointers to reference necessary classes
GameMechs *gamemech;
Player *player1;
Food *foodObj;



void Initialize(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    //continue game loop while exit flag is false
    while(gamemech->getExitFlagStatus() == false)  
    {
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

    //default board size is 30 x 15
    //we are using game board with size 30 x 15 but using specialized constructor
    gamemech = new GameMechs(30, 15);

    foodObj = new Food(gamemech);

    player1 = new Player(gamemech, foodObj);
    objPosArrayList* player1Body = player1->getPlayerPos();

    //generate food items while avoiding player's arrayList body
    foodObj->generateFood(*player1Body);   
}

void RunLogic(void)
{
    player1->updatePlayerDir();
    player1->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    //if game exit flag true
    if(gamemech->getExitFlagStatus())
    {
        //if lose flag also true
        if(gamemech->getLoseFlagStatus())
        {
            MacUILib_printf("The snake ate itself! You Scored: %d.\n", gamemech->getScore());
        }
        else
        {
            MacUILib_printf("Game Ended. You Scored: %d.\n", gamemech->getScore());
        }
        
        return;
    }

    objPos foodPos,BodySeg;
    bool body_drawn, food_drawn;

    objPosArrayList* player1Body = player1->getPlayerPos();
    objPosArrayList* foodPositions = foodObj->getFoodPos();

    for(int i = 0; i < gamemech->getBoardSizeY(); i++)
    {
        for(int j = 0; j < gamemech->getBoardSizeX(); j++)
        {
            body_drawn = false;

            //first check for player body positions
            for (int k = 0; k<player1Body->getSize();k++)
            {
                player1Body -> getElement(BodySeg, k);

                if (j == BodySeg.x && i == BodySeg.y)
                {
                    body_drawn = true;
                    MacUILib_printf("%c",BodySeg.symbol);
                    break;
                }
            }

            if (!body_drawn)
            {
                food_drawn = false;
                
                //check for positions of food objects
                for(int k = 0; k < foodPositions->getSize(); k++)
                {
                    foodPositions -> getElement(foodPos, k);
                    if (j == foodPos.x && i == foodPos.y)
                    {
                        food_drawn = true;
                        MacUILib_printf("%c",foodPos.symbol);
                        break;
                    }
                }

                //if no food object or player object at position, print gameboard value
                if(!food_drawn)
                {
                    if(i == 0 || i == gamemech->getBoardSizeY() - 1 || j == 0 || j == gamemech->getBoardSizeX() - 1)
                    {
                        MacUILib_printf("#");
                    }
                    else
                    {
                        MacUILib_printf(" ");
                    }
                }    
            }
        }
        MacUILib_printf("\n");
    }   

    
    //Score and Debugging Messages
    player1Body->getHeadElement(BodySeg);
    MacUILib_printf("Score: %d", gamemech->getScore());
    MacUILib_printf("\n======== DEBUG MESSAGE ========");
    MacUILib_printf("\nBoard Size: %dx%d", gamemech->getBoardSizeX(), gamemech->getBoardSizeY());
    MacUILib_printf("\nPlayer Direction: %c", player1->getPlayerDir());
    MacUILib_printf("\nPlayer Postion: %d, %d", BodySeg.x, BodySeg.y);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_uninit();

    //free object pointers
    delete player1;
    delete foodObj;
    delete gamemech;
}
