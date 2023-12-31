#ifndef GAMEMECHS_H
#define GAMEMECHS_H

class GameMechs
{
    private:
        char input;
        bool exitFlag;

        bool loseFlag;
        int score;
        
        int boardSizeX;
        int boardSizeY;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        bool getExitFlagStatus();
        void setExitTrue();

        bool getLoseFlagStatus();
        void setLoseFlag();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getScore();
        void incrementScore(int amount);

        int getBoardSizeX();
        int getBoardSizeY();
      

};

#endif