#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iostream>
#include "Square.h"
class Chessboard{
    public:
        Chessboard();

        ~Chessboard();

        Chessboard& operator=(const Chessboard& OTHER);

        Square** getBoard() const;

        string getCapturedPieces(bool white) const;

        string move(const string FROM, const string TO, bool isPlayerWhite);

        bool** getCastlingRights();
    private:
        
        Square** mpChessboard;
        string mWhiteCapturedPieces;
        string mBlackCapturedPieces;
        //queenside rook, king, kingside rook
        //first rank white, second rank black.
        bool** mPRookKingRookHasMoved;
        string* mKingSquare;
};

ostream& operator<<(ostream& os, const Chessboard& BOARD);

#endif