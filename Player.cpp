#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    //assign global object pointers from project.cpp to local object pointers 
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;

    myDir = STOP;
    playerPosList = new objPosArrayList();

    //add 1 player object into gameboard
    objPos startPos;
    startPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2,'*');
    playerPosList->insertHead(startPos);
}

Player::~Player()
{
    //deallocate player object arrayList
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
    // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
    char input;
    input = mainGameMechsRef->getInput();

    if (input != 0){
        //if input is capital letter, set to lowercase
        if(input >= 'A' && input <= 'Z')
        {
            input += 32;
        }

        switch(input)
        {
            //if input is space bar, set exit flag to true
            case ' ':
                mainGameMechsRef->setExitTrue();
                break;
            
            //If input 'w' and myDir is NOT DOWN, player goes up
            case 'w':
                if(myDir != DOWN)
                    myDir = UP;
                break;

            //if input 'a' and myDir is NOT RIGHT, player goes left
            case 'a':
                if(myDir != RIGHT)
                    myDir = LEFT;
                break;

            //if input 's' and myDir is NOT UP, player goes down
            case 's':
                if(myDir != UP)
                    myDir = DOWN;
                break;

            //If input 'd' and myDir is NOT LEFT, player goes right
            case 'd':
                if(myDir != LEFT)
                    myDir = RIGHT;
                break;

            default:
                break;
        }
    }
    input = 0;
    //clear the most recent input (input = NULL)
    mainGameMechsRef->clearInput();
}

void Player::updateMovement(objPos &currentHeadPos)
{
    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    //change position based on current associated direction value of myDir 
    //implement border wrap around in each position changing case

    if (myDir == UP){
        currentHeadPos.y--;
        if (currentHeadPos.y <= 0){
            currentHeadPos.y = boardY - 2;
        }
    }
    else if (myDir == DOWN){
        currentHeadPos.y++;
        if (currentHeadPos.y >= boardY - 1){
            currentHeadPos.y = 1;
        }
    }
    else if (myDir == LEFT){
        currentHeadPos.x--;
        if (currentHeadPos.x <= 0){
            currentHeadPos.x = boardX - 2;
        }
    }
    else if (myDir == RIGHT){
        currentHeadPos.x++;
        if (currentHeadPos.x >= boardX - 1){
            currentHeadPos.x = 1;
        }
    }
}

void Player::movePlayer()
{
    //get position of player head
    objPos currentHeadPos;
    objPos bodySeg;

    char symbol;

    playerPosList->getHeadElement(currentHeadPos);

    //check for player head overlap with other body positions (snake suicide)
    for(int i = 1; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(bodySeg, i);
        if(currentHeadPos.isPosEqual(&bodySeg)){
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            return;
        }     
    }

    updateMovement(currentHeadPos);

    playerPosList->insertHead(currentHeadPos);

    //check whether the head overlaps with food position
    if(checkFoodConsumption(currentHeadPos, symbol))
    {
        //if head overlaps food object, change player length and generate new food positions
        changePlayerLength(currentHeadPos, symbol);
        foodRef->generateFood(*playerPosList);
    }
    else
    {
        playerPosList->removeTail();
    }
}

bool Player::checkFoodConsumption(objPos currentHeadPos, char &symbol)
{
    objPos foodPos;
    objPosArrayList* foodPositions = foodRef->getFoodPos();

    //check for head overlap with each object in the player arrayList
    for(int i = 0; i < foodPositions->getSize(); i++)
    {
        foodPositions->getElement(foodPos, i);
        if(foodPos.isPosEqual(&currentHeadPos))
        {
            symbol = foodPos.getSymbolIfPosEqual(&currentHeadPos);
            return true;
        }
    }

    return false;
}

void Player::changePlayerLength(objPos currentHeadPos, char symbol)
{
    int chances;

    //if head overlapped with symbol '?'
    if(symbol == '?')
    {
        chances = rand() % 3;
        switch(chances)
        {
            case 0:
                //increase size by 4 (3 here, 1 in movePlayer() method), keep score the same
                for(int i = 0; i < 3; i++)
                {
                    updateMovement(currentHeadPos);
                    playerPosList->insertHead(currentHeadPos);
                }
                break;

            case 1:
                //increase score by 10, and keep size same
                mainGameMechsRef->incrementScore(10);
                playerPosList->removeTail();
                break;

            case 2:
                //decrease score by 5, keep same size
                mainGameMechsRef->incrementScore(-5);
                playerPosList->removeTail();
                break;

            default:
                mainGameMechsRef->incrementScore(1);
                break;
        }
    }
    //if player consumes any food object other than '?'
    else
    {
        mainGameMechsRef->incrementScore(1);
    }
}

//return character of player's current direction
char Player::getPlayerDir(){
    switch(myDir){
            case LEFT:
                return('L');
                break;
            case RIGHT:
                return('R');
                break;
            case UP:
                return('U');
                break;
            case DOWN:
                return('D');
                break;
            default:
                return('S');
    }
}