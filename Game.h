#ifndef GAME_H
#define GAME_H
#include "Chessboard.h"
#include <fstream>
using namespace std;
class Game{
    public:
        void run();
        Game();
        ~Game();
        void test();
    private:
        Chessboard* mpBoard;
        string mMoves;
        int mMoveNumber;
        ofstream logger;
};
#endif