#include "Game.h"
#include "Chessboard.h"
#include <iostream>
#include <fstream>
using namespace std;

Game::Game(){
    mMoveNumber = 1;
    mMoves = "";
    mpBoard  = new Chessboard();
    logger.open("game log.txt", _S_app);
}
void Game::test(){
    //change col and row to see potential moves for any piece
    char col = 'e';
    int row = 1;
    cout<<mpBoard->getBoard()[col-97][row-1].potentialMoves(mpBoard->getBoard(), mpBoard->getCastlingRights(), "e1")<<endl;

    cout<<*mpBoard;
}
void Game::run(){
    cout<<*mpBoard;
    string from;
    string to;
    string player1;
    string player2;
    string result;

    cout<<"Enter player 1's name: ";
    cin>>player1;
    cout<<"Enter player 2's name: ";
    cin>>player2;
    //game loop
    while(true){
        //white
        while(true){

            //read input
            cout<<player1<<"'s turn!\nEnter your move: ";
            cin>>from>>to;
            if(from == "q"||to=="q"){
                break;
            }

            //validate
            if(cin.fail()||from.length()!=2||to.length()!=2){
                cout<<"Invalid input"<<endl;
                cin.clear();
                char clearCin;
                while(cin.get()!='\n'){
                    clearCin = cin.get();
                }
                continue;
            }
            //make the move and deal with the result accordingly
            result = mpBoard->move(from, to, 1);
                mMoves = mMoves+to_string(mMoveNumber)+". "+from+" to "+to+", ";
                mMoveNumber++;
                cout<<*mpBoard;
                cout<<mMoves<<endl;
            if(result=="continue"){
                break;
            }else if (result=="checkmate"){
                cout<<"White Wins!"<<endl;
                logger<<player1<<"(White) beat "<<player2<<"(Black)"<<endl;
                logger<<*mpBoard<<endl;
                logger<<mMoves<<endl<<endl<<endl;
                return;
            }else if (result=="stalemate"){

                logger<<player1<<"(White) drew "<<player2<<"Black"<<endl;
                logger<<*mpBoard<<endl;
                logger<<mMoves<<endl<<endl<<endl;

                cout<<"Draw!"<<endl;
                return;
            }else{
                cout<<result<<endl;
            }
            
        }
        if(from == "q"||to=="q"){
            break;
        }
        //black
        while(true){
            //read
            cout<<player2<<"'s turn!\nEnter your move: ";
            cin>>from>>to;
            if(from == "q"||to=="q"){
                break;
            }

            //validate
            if(cin.fail()||from.length()!=2||to.length()!=2){
                cout<<"Invalid input"<<endl;
                cin.clear();
                char clearCin;
                while(cin.get()!='\n'){
                    clearCin = cin.get();
                }
                continue;
            }
            
            //make the move and deal with the result accordingly
            result = mpBoard->move(from, to, 0);
                mMoves = mMoves+from+" to "+to+" ";
                cout<<*mpBoard;
                cout<<mMoves<<endl;
            if(result=="continue"){
                break;
            }else if (result=="checkmate"){
                cout<<"Black Wins!"<<endl;

                logger<<player2<<"(Black) beat "<<player1<<"(White)"<<endl;
                logger<<*mpBoard<<endl;
                logger<<mMoves<<endl<<endl<<endl;

                return;
            }else if (result=="stalemate"){
                cout<<"Draw!"<<endl;

                logger<<player1<<"(White) drew "<<player2<<"(Black)"<<endl;
                logger<<*mpBoard<<endl;
                logger<<mMoves<<endl<<endl<<endl;

                return;
            }else{
                cout<<result<<endl;
            }
        }
        if(from == "q"||to=="q"){
            break;
        }
    }
}
Game::~Game(){
    logger.close();
    delete mpBoard;
}