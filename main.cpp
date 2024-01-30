//#include "Chessboard.h"
#include "Game.h"
#include <iostream>
using namespace std;


int main(){
    Game* game = new Game();
    game->run();
    delete game;
}