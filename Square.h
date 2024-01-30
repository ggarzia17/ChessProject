#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>

using namespace std;
class Square{
    public:
        Square();
        Square(const char PIECE_TYPE, const string POS, const bool WHITE);
        ~Square();
        void setPos(string newPos);
        bool isEmpty() const;
        Square& operator=(const Square& OTHER);
        bool isPieceWhite() const;
        char type() const;
        string pos() const;
        string potentialMoves(Square** board, bool** castlingRights, string kingSquare);

        bool isInCheck(Square** board, bool areAttackingPiecesWhite, bool** castlingRigths);

        void promote();
    private:
        string potentialMovesRook(Square** board, bool** castlingRights, string kingSquare);
        string potentialMovesPawn(Square** board, bool** castlingRights, string kingSquare);
        string potentialMovesKing(Square** board, bool** castlingRights, string kingSquare);
        string potentialMovesKnight(Square** board, bool** castlingRights, string kingSquare);
        string potentialMovesBishop(Square** board, bool** castlingRights, string kingSquare);
        string potentialMovesQueen(Square** board, bool** castlingRights, string kingSquare);
        char mPieceType;
        string mPos;
        bool mIsPieceWhite;
};

ostream& operator<<(ostream& os, const Square& SQUARE);
#endif