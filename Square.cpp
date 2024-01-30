#include "Square.h"
#include <iostream>
#include <string>
using namespace std;

Square::Square(const char PIECE_TYPE, const string POS, const bool WHITE){
    mPieceType = PIECE_TYPE;
    mPos = POS;
    mIsPieceWhite = WHITE;
}

Square::Square(){
}

Square::~Square(){
}

Square& Square::operator=(const Square& OTHER){
    if(&OTHER == this){
        return *this;
    }
    mPieceType = OTHER.type();
    mPos = OTHER.pos();
    mIsPieceWhite = OTHER.isPieceWhite();

    return *this;
}

bool Square::isEmpty() const{
    return mPieceType==' ';
}
char Square::type() const{
    return mPieceType;
}

bool Square::isPieceWhite() const{
    return mIsPieceWhite;
}

string Square::pos() const{
    return mPos;
}

ostream& operator<<(ostream& os, const Square& SQUARE){
    if(SQUARE.isEmpty()){
        os<<" ";
        return os;
    }
    if(SQUARE.isPieceWhite()){
        os<<(char)toupper(SQUARE.type());
    }else{
        os<<SQUARE.type();
    }
    return os;
}

string Square::potentialMoves(Square** board, bool** castlingRights, string kingSquare){
    switch(mPieceType){
        case 'k':
            return potentialMovesKing(board, castlingRights, kingSquare);
            break;
        case 'q':
            return potentialMovesQueen(board, castlingRights, kingSquare);
            break;
        case 'n':
            return potentialMovesKnight(board, castlingRights, kingSquare);
            break;
        case 'p':
            return potentialMovesPawn(board, castlingRights, kingSquare);
            break;
        case 'r':
            return potentialMovesRook(board, castlingRights, kingSquare);
            break;
        case 'b':
            return potentialMovesBishop(board, castlingRights, kingSquare);
            break;
        default:
            return " ";
        
    }
}

string Square::potentialMovesRook(Square** board, bool** castlingRights, string kingSquare){
    string moves = "";

    //left
    for(char i = mPos[0]+1; i<='h'; i++){
        if(!board[i-97][mPos[1]-49].isEmpty()){
            if(board[i-97][mPos[1]-49].isPieceWhite()!=mIsPieceWhite){
                moves += (char)i;
                moves += mPos[1];
                moves += " ";
            }
            break;
        }
        moves += (char)i;
        moves += mPos[1];
        moves += " ";
    }

    //right
    for(char i = mPos[0]-1; i>='a'; i--){
        if(!board[i-97][mPos[1]-49].isEmpty()){
            if(board[i-97][mPos[1]-49].isPieceWhite()!=mIsPieceWhite){
                moves += (char)i;
                moves += mPos[1];
                moves += " ";
            }
            break;
        }
        moves += (char)i;
        moves += mPos[1];
        moves += " ";
    }

    //up
    for(int i = ((int)mPos[1]-47); i<=8; i++){
        if(!board[mPos[0]-97][i-1].isEmpty()){
            if(board[mPos[0]-97][i-1].isPieceWhite()!=mIsPieceWhite){
                moves += mPos[0];
                moves += to_string(i);
                moves += " ";
            }
            break;
        }
        moves += mPos[0];
        moves += to_string(i);
        moves += " ";
    }

    //down
    for(int i = ((int)mPos[1]-49); i>=1; i--){
        if(!board[mPos[0]-97][i-1].isEmpty()){
            if(board[mPos[0]-97][i-1].isPieceWhite()!=mIsPieceWhite){
                moves += mPos[0];
                moves += to_string(i);
                moves += " ";
            }
            break;
        }
        moves += mPos[0];
        moves += to_string(i);
        moves += " ";
    }
    return moves;
}
string Square::potentialMovesPawn(Square** board, bool** castlingRights, string kingSquare){
    string moves = "";

    if(mIsPieceWhite){
        //normal 1 square move
        if(board[mPos[0]-97][mPos[1]-48].isEmpty()){
            moves += mPos[0];
            moves += to_string((int)mPos[1]-47);
            moves += " ";
            

            //initial two square move
            if(mPos[1]=='2'&&board[mPos[0]-97][mPos[1]-47].isEmpty()){
                moves += mPos[0];
                moves += to_string((int)mPos[1]-46);
                moves += " ";
            }
        }

        //left capture
        if((!(mPos[0]=='a')&&!(board[mPos[0]-98][mPos[1]-48].isPieceWhite()))&&!(board[mPos[0]-98][mPos[1]-48].isEmpty())){
            moves += mPos[0]-1;
            moves += to_string((int)mPos[1]-47);
            moves += " ";
        }

        //right capture
        if((!(mPos[0]=='h')&&!(board[mPos[0]-96][mPos[1]-48].isPieceWhite()))&&!(board[mPos[0]-96][mPos[1]-48].isEmpty())){
            moves += mPos[0]+1;
            moves += to_string((int)mPos[1]-47);
            moves += " ";
        }
    }else{
        //normal one square move
        if(board[mPos[0]-97][mPos[1]-50].isEmpty()){
            moves += mPos[0];
            moves += to_string((int)mPos[1]-49);
            moves += " ";
            //initial two square move
            if(mPos[1]=='7'&&board[mPos[0]-97][mPos[1]-51].isEmpty()){
                moves += mPos[0];
                moves += to_string((int)mPos[1]-50);
                moves += " ";
            }
        }

        //right capture
        if((!(mPos[0]=='a')&&board[mPos[0]-98][mPos[1]-50].isPieceWhite())&&!(board[mPos[0]-98][mPos[1]-50].isEmpty())){
            moves += mPos[0]-1;
            moves += to_string((int)mPos[1]-49);
            moves += " ";
        }

        //left capture
        if((!(mPos[0]=='h')&&board[mPos[0]-96][mPos[1]-50].isPieceWhite())&&!(board[mPos[0]-96][mPos[1]-50].isEmpty())){
            moves += mPos[0]+1;
            moves += to_string((int)mPos[1]-49);
            moves += " ";
        }
    }
    return moves;
}
string Square::potentialMovesKing(Square** board, bool** castlingRights, string kingSquare){
    string moves = "";
    // Square toSquare;
    // string tempPos;
    for(int i = -1; i<2; i++){
        if(!(mPos[0]-97+i>7||mPos[0]-97+i<0)){
            for(int j = -1; j<2; j++){
                
                if(!(mPos[1]-49+j>7||mPos[1]-49+j<0)&&(board[mPos[0]-97+i][mPos[1]-49+j].isEmpty()
                ||board[mPos[0]-97+i][mPos[1]-49+j].isPieceWhite()!=mIsPieceWhite)&&!(j==0&&i==0)){

                    if(!board[mPos[0]-97+i][mPos[1]-49+j].isInCheck(board, !mIsPieceWhite, castlingRights)){
                        moves += mPos[0]+i;
                        moves += mPos[1]+j;
                        moves += " ";
                    }
                }
            }
        }
    }

    //castling sucks
    if(board[mPos[0]-97][mPos[1]-49].isInCheck(board, !mIsPieceWhite, castlingRights)){
        return moves;
    }
    if(!castlingRights[((int)!isPieceWhite())][1]){
        if(!castlingRights[((int)!isPieceWhite())][0]){
            if(board[1][((int)!isPieceWhite())*7].type()==' '&&board[2][((int)!isPieceWhite())*7].type()==' '&&
            board[3][((int)!isPieceWhite())*7].type()==' '){
                if(!board[1][((int)!isPieceWhite())*7].isInCheck(board, !isPieceWhite(), castlingRights)
                &&!board[2][((int)!isPieceWhite())*7].isInCheck(board, !isPieceWhite(), castlingRights)&&
                !board[3][((int)!isPieceWhite())*7].isInCheck(board, !isPieceWhite(), castlingRights)){
                    moves+="c"+to_string(((int)!isPieceWhite())*7+1)+" ";
                }
            }
        }
        if(!castlingRights[((int)!isPieceWhite())][2]){
            if(board[6][((int)!isPieceWhite())*7].type()==' '&&board[5][((int)!isPieceWhite())*7].type()==' '){
                if(!board[6][((int)!isPieceWhite())*7].isInCheck(board, !isPieceWhite(), castlingRights)
                &&!board[5][((int)!isPieceWhite())*7].isInCheck(board, !isPieceWhite(), castlingRights)){
                    moves+="g"+to_string(((int)!isPieceWhite())*7+1)+" ";
                }
            }
        }
    }
    return moves;
}
string Square::potentialMovesKnight(Square** board, bool** castlingRights, string kingSquare){
    string to;
    string moves = "";
    
    //move one file over and two rows up or down
    for(int i = -1; i<2; i+=2){

        if(!(mPos[0]-97+i>7||mPos[0]-97+i<0)){

            for(int j = -2; j<3; j+=4){

                if(!(mPos[1]-48+j>8||mPos[1]-48+j<=0)&&(board[mPos[0]-97+i][mPos[1]-49+j].isEmpty()
                ||board[mPos[0]-97+i][mPos[1]-49+j].isPieceWhite()!=mIsPieceWhite)){
                    moves += mPos[0]+i;
                    moves += mPos[1]+j;
                    moves += " ";
                }
                
            }
        }
    }

    //move two files over and one row up or down
    for(int i = -2; i<3; i+=4){

        if(!(mPos[0]-97+i>7||mPos[0]-97+i<0)){

            for(int j = -1; j<2; j+=2){

                if(!(mPos[1]-48+j>8||mPos[1]-48+j<=0)&&(board[mPos[0]-97+i][mPos[1]-49+j].isEmpty()
                ||board[mPos[0]-97+i][mPos[1]-49+j].isPieceWhite()!=mIsPieceWhite)){
                    moves += mPos[0]+i;
                    moves += mPos[1]+j;
                    moves += " ";
                }
                
            }
        }
    }

    return moves;
}
string Square::potentialMovesBishop(Square** board, bool** castlingRights, string kingSquare){
    string to;
    string moves = "";

    int i = mPos[0]-96;
    int j = mPos[1]-48;
    //upper right
    while(i<8&&j<8&&i>=0&&j>=0){
        if(!board[i][j].isEmpty()&&(board[i][j].isPieceWhite()==board[mPos[0]-97][mPos[1]-49].isPieceWhite())){
            break;
        }
        moves += i+97;
        moves += j+49;
        moves += " ";

        if(!board[i][j].isEmpty()&&(board[i][j].isPieceWhite()!=board[mPos[0]-97][mPos[1]-49].isPieceWhite())){
            break;
        }
        i++;
        j++;
    }

    i = mPos[0]-96;
    j = mPos[1]-50;
    //lower right
    while(i<8&&j<8&&i>=0&&j>=0){
        if(!board[i][j].isEmpty()&&(board[i][j].isPieceWhite()==board[mPos[0]-97][mPos[1]-49].isPieceWhite())){
            break;
        }
        moves += i+97;
        moves += j+49;
        moves += " ";

        if(!board[i][j].isEmpty()&&(board[i][j].isPieceWhite()!=board[mPos[0]-97][mPos[1]-49].isPieceWhite())){
            break;
        }
        i++;
        j--;
    }

    i = mPos[0]-98;
    j = mPos[1]-48;
    //upper left
    while(i<8&&j<8&&i>=0&&j>=0){
        if(!board[i][j].isEmpty()&&(board[i][j].isPieceWhite()==board[mPos[0]-97][mPos[1]-49].isPieceWhite())){
            break;
        }
        moves += i+97;
        moves += j+49;
        moves += " ";

        if(!board[i][j].isEmpty()&&(board[i][j].isPieceWhite()!=board[mPos[0]-97][mPos[1]-49].isPieceWhite())){
            break;
        }
        i--;
        j++;
    }

    i = mPos[0]-98;
    j = mPos[1]-50;
    //lower left
    while(i<8&&j<8&&i>=0&&j>=0){
        if(!board[i][j].isEmpty()&&(board[i][j].isPieceWhite()==board[mPos[0]-97][mPos[1]-49].isPieceWhite())){
            break;
        }
        moves += i+97;
        moves += j+49;
        moves += " ";

        if(!board[i][j].isEmpty()&&(board[i][j].isPieceWhite()!=board[mPos[0]-97][mPos[1]-49].isPieceWhite())){
            break;
        }
        i--;
        j--;
    }

   

    return moves;
}
string Square::potentialMovesQueen(Square** board, bool** castlingRights, string kingSquare){
    return potentialMovesBishop(board, castlingRights, kingSquare) +potentialMovesRook(board, castlingRights, kingSquare);
}

void Square::setPos(string newPos){
    if(newPos[0]>='a'&&newPos[0]<='h'&&newPos[1]>='1'&&newPos[1]<='8'){
        mPos = newPos;
    }else{cout<<"invalid pos"<<endl;}
}

bool Square::isInCheck(Square** board, bool areAttackingPiecesWhite, bool** castlingRights){
    //check if all pieces can move to the attacked square
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if(board[i][j].isPieceWhite()==areAttackingPiecesWhite&&board[i][j].type()!=' '){

                if(board[i][j].type()!='k'&&board[i][j].type()!='p'
                &&board[i][j].potentialMoves(board, castlingRights, mPos).find(mPos)!=string::npos){
                    return true;
                }
                if(board[i][j].type()=='p'&&!(i+areAttackingPiecesWhite*2-1<8||i+areAttackingPiecesWhite*2-1>=0)&&(board[i+areAttackingPiecesWhite*2-1][j+1].pos()==mPos||board[i+areAttackingPiecesWhite*2-1][j-1].pos()==mPos)){
                    return true;
                }if(board[i][j].type()=='k'){
                    for(int k = -1; k<2; k++){
                        for(int l = -1; l<2; l++){
                            if((i+k>=0&&i+k<8&&j+l>=0&&j+l<8)&&board[i+k][j+l].pos()==mPos){
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

void Square::promote(){
    char promotion;
    while(true){
        cout<<"What would you like to promote to: Queen (q), Rook (r), Bishop (b), or Knight (n)? ";
        cin>>promotion;
        promotion = tolower(promotion);
        if(cin.fail()||(promotion!='q'&&promotion!='r'&&promotion!='b'&&promotion!='n')){
            cout<<"Invalid promotion"<<endl;
            cin.clear();
            while(cin.get()){
                cin.get();
            }
            continue;
        }
        break;
    }
    mPieceType = promotion;
}