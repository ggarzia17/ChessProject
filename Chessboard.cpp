#include "Chessboard.h"
#include "Square.h"
#include <iostream>
using namespace std;

//constructor
Chessboard::Chessboard(){
    //edit starting state here
    string startingState = "RNBQKBNR/PPPPPPPP/        /        /        /        /pppppppp/rnbqkbnr/";//"RNBQKBNR/PPPPPPPP/        /        /        /        /pppppppp/rnbqkbnr/";
    mPRookKingRookHasMoved = new bool*[2];
    mpChessboard = new Square*[8];
    string pos;
    mBlackCapturedPieces = "";
    mWhiteCapturedPieces = "";
    mKingSquare = new string[2];
    mKingSquare[0] = "e1";
    mKingSquare[1] = "e8";

    //initialize empty board
    for(int i = 0; i<8; i++){
        mpChessboard[i] = new Square[8];
    }
    //initialize king and rook has moved to false
    for (int i = 0; i<2; i++){
        mPRookKingRookHasMoved[i] = new bool[3];
    }
    //set board up according to starting state
    for(int i = 0; i < startingState.length(); i++){
        if(startingState[i]!='/'){
            pos = (char)(i%9+97)+to_string(1+i/9);
            // cout<<pos<<" "<<startingState[i]<<" "<<isupper(startingState[i])<<endl;
            mpChessboard[i%9][i/9] = Square(tolower(startingState[i]), pos, isupper(startingState[i]));
            
            
        }
    }
}

//destructor
Chessboard::~Chessboard(){
    for(int i = 0; i<8; i++){
        delete mpChessboard[i];
    }
    delete mpChessboard;
}

//copy assignment operator
Chessboard& Chessboard::operator=(const Chessboard& OTHER){
    if(this==&OTHER){
        return *this;
    }

    
    delete this;

    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            mpChessboard[j][i] = OTHER.getBoard()[j][i];
        }
    }
    return *this;
}

//getter
Square** Chessboard::getBoard() const{
    return mpChessboard;
}

//checks if a move is vaild and performs move if valid
string Chessboard::move(const string FROM, const string TO, bool isPlayerWhite){
    if(!(FROM[0]<='h'&&FROM[0]>='a')||!(TO[0]<='h'&&TO[0]>='a')||!(FROM[1]<='8'&&FROM[1]>='1')||!(TO[1]<='8'&&TO[1]>='1')){
        return "invalid positions";
    }
    Square capturedPiece = mpChessboard[(int)(TO[0]-97)][(int)(TO[1]-49)];
    bool isWhite = mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)].isPieceWhite();

    if(mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)].isPieceWhite()!=isPlayerWhite){
        return "wrong color";
    }
    //checks if move is valid
    if(mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)].potentialMoves(mpChessboard, mPRookKingRookHasMoved, mKingSquare[!mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)].isPieceWhite()]).find(TO)!=string::npos){

        //checks to see if castling is affected
        if(isWhite){
            if(mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)].type()=='r'){
                if(FROM=="a1"){
                    mPRookKingRookHasMoved[0][0]=1;
                }else if(FROM=="h1"){
                    mPRookKingRookHasMoved[0][2]=1;
                }
            }else if(mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)].type()=='k'){
                if(FROM=="e1"){
                    mPRookKingRookHasMoved[0][1]=1;
                }
            } 
        }
        if(!isWhite){
            if(mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)].type()=='r'){
                if(FROM=="a8"){
                    mPRookKingRookHasMoved[1][0]=1;
                }else if(FROM=="h8"){
                    mPRookKingRookHasMoved[1][2]=1;
                }
            }else if(mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)].type()=='k'){
                if(FROM=="e8"){
                    mPRookKingRookHasMoved[1][1]=1;
                }
            } 
        }
        
        //change king square
        if(mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)].type()=='k'){
            mKingSquare[!isWhite] = TO;
        }
        //performs move
        mpChessboard[(int)(TO[0]-97)][(int)(TO[1]-49)] = mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)];
        mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)] = Square(' ', FROM, 0);
        mpChessboard[(int)(TO[0]-97)][(int)(TO[1]-49)].setPos(TO);
        
        //make sure king isnt in check after move
        if(mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)].type()!='k'
        &&mpChessboard[mKingSquare[!isWhite][0]-97][mKingSquare[!isWhite][1]-49].isInCheck(mpChessboard, !isWhite, mPRookKingRookHasMoved)){

            mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)] = mpChessboard[(int)(TO[0]-97)][(int)(TO[1]-49)];
            mpChessboard[(int)(TO[0]-97)][(int)(TO[1]-49)] = capturedPiece;
            mpChessboard[(int)(FROM[0]-97)][(int)(FROM[1]-49)].setPos(FROM);
            mKingSquare[!isWhite] = FROM;
            return "cant put king in check";
        }

        //move rook if castling
        if(mpChessboard[(int)(TO[0]-97)][(int)(TO[1]-49)].type()=='k'&&TO=="g1"&&FROM=="e1"){
            mpChessboard[5][0] = mpChessboard[7][0];
            mpChessboard[7][0] = Square(' ', "h1", 0);
            mpChessboard[5][0].setPos("f1");
        }
        if(mpChessboard[(int)(TO[0]-97)][(int)(TO[1]-49)].type()=='k'&&TO=="c1"&&FROM=="e1"){
            mpChessboard[3][0] = mpChessboard[0][0];
            mpChessboard[0][0] = Square(' ', "a1", 0);
            mpChessboard[3][0].setPos("d1");
        }
        if(mpChessboard[(int)(TO[0]-97)][(int)(TO[1]-49)].type()=='k'&&TO=="g8"&&FROM=="e8"){
            mpChessboard[5][7] = mpChessboard[7][7];
            mpChessboard[7][7] = Square(' ', "h8", 0);
            mpChessboard[5][7].setPos("f8");
        }
        if(mpChessboard[(int)(TO[0]-97)][(int)(TO[1]-49)].type()=='k'&&TO=="c8"&&FROM=="e8"){
            mpChessboard[3][7] = mpChessboard[0][7];
            mpChessboard[0][7] = Square(' ', "a8", 0);
            mpChessboard[3][7].setPos("d8");
        }

        //updates captured pieces
        if(capturedPiece.type()!=' '){
            if(capturedPiece.isPieceWhite()){
                mWhiteCapturedPieces = mWhiteCapturedPieces + " "+(char)toupper(capturedPiece.type());
            }else{
                mBlackCapturedPieces = mBlackCapturedPieces + " "+(char)capturedPiece.type();
            }
        }

        //print check if opponent is in check
        string kingSquare = mKingSquare[isPlayerWhite];
        if(mpChessboard[(int)(kingSquare[0]-97)][(int)(kingSquare[1]-49)].isInCheck(mpChessboard, isPlayerWhite, mPRookKingRookHasMoved)){
            cout<<"Check!"<<endl;
        }

        //promotions
        if(mpChessboard[(int)(TO[0]-97)][(int)(TO[1]-49)].type()=='p'&&(TO[1]=='8'||TO[1]=='1')){
            mpChessboard[(int)(TO[0]-97)][(int)(TO[1]-49)].promote();
        }

        //checkmate
        string moves;
        string tryTo;
        Square tryToSquare;
        string saveKingSquare = mKingSquare[isPlayerWhite];
        string savePos;
        bool hasValidMove = false;
        for(int i = 0; i<8&&!hasValidMove; i++){

            for(int j = 0; j<8&&!hasValidMove; j++){

                if(mpChessboard[i][j].isPieceWhite()!=isPlayerWhite&&!mpChessboard[i][j].isEmpty()){

                    moves = mpChessboard[i][j].potentialMoves(mpChessboard, mPRookKingRookHasMoved, mKingSquare[isPlayerWhite]);
                    
                    while(moves.length()>1){

                        tryTo = moves.substr(0, 2);
                        tryToSquare = mpChessboard[(int)(tryTo[0]-97)][(int)(tryTo[1]-49)];

                        if(mpChessboard[i][j].type()=='k'){
                            mKingSquare[isPlayerWhite]=tryTo;
                        }
                        savePos = mpChessboard[i][j].pos();

                        mpChessboard[(int)(tryTo[0]-97)][(int)(tryTo[1]-49)] = mpChessboard[i][j];
                        mpChessboard[i][j] = Square(' ', "a1", 0);
                        
                        mpChessboard[(int)(tryTo[0]-97)][(int)(tryTo[1]-49)].setPos(tryTo);
                        
                        if(!mpChessboard[(int)(mKingSquare[isPlayerWhite][0]-97)][(int)(mKingSquare[isPlayerWhite][1]-49)].isInCheck(mpChessboard, isPlayerWhite, mPRookKingRookHasMoved)){

                            mpChessboard[i][j] = mpChessboard[(int)(tryTo[0]-97)][(int)(tryTo[1]-49)];
                            mpChessboard[(int)(tryTo[0]-97)][(int)(tryTo[1]-49)] = tryToSquare;
                            if(mpChessboard[i][j].type()=='k'){
                                mKingSquare[isPlayerWhite]=saveKingSquare;
                            }
                            mpChessboard[i][j].setPos(savePos);
                            
                            hasValidMove=true;
                            break;

                        }
                        mpChessboard[i][j] = mpChessboard[(int)(tryTo[0]-97)][(int)(tryTo[1]-49)];
                        mpChessboard[(int)(tryTo[0]-97)][(int)(tryTo[1]-49)] = tryToSquare;
                        if(mpChessboard[i][j].type()=='k'){
                            mKingSquare[isPlayerWhite]=saveKingSquare;
                        }
                        mpChessboard[i][j].setPos(savePos);
                        

                        moves = moves.substr(3);
                    }
                }
            }
        }
        if(!hasValidMove&&
        mpChessboard[(int)(mKingSquare[isPlayerWhite][0]-97)][(int)(mKingSquare[isPlayerWhite][1]-49)].isInCheck(mpChessboard, isPlayerWhite, mPRookKingRookHasMoved)){
            cout<<"Checkmate!"<<endl;
            return "checkmate";
        }else if(!hasValidMove){
            cout<<"Stalemate"<<endl;
            return "stalemate";
        }

        return "continue";
    }else{
        //if invalid
        return "else invalid";
    }
}

//returns captured pieces
string Chessboard::getCapturedPieces(bool white) const{
    if(white){
        return mBlackCapturedPieces;
    }
    return mWhiteCapturedPieces;
}

//prints out the board including moves and captured pieces
ostream& operator<<(ostream& os, const Chessboard& BOARD){
    os<<"Captured Pieces: "<<BOARD.getCapturedPieces(0)<<endl;
    os<<"  ---------------------------------"<<endl;
    for (int i = 0; i<8; i++){
        os<<8-i<<" | ";
        for(int j = 0; j<8; j++){
            os<<BOARD.getBoard()[j][7-i]<<" | ";
        }
        os<<endl;
        os<<"  ---------------------------------"<<endl;
    }
    os<<"    A   B   C   D   E   F   G   H  "<<endl;
    os<<"Captured Pieces: "<<BOARD.getCapturedPieces(1)<<endl;
    return os;
}

bool** Chessboard::getCastlingRights(){
    return mPRookKingRookHasMoved;
}