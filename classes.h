#include <string>

using namespace std;

class Piece {
    public: 
        string color;
        int row; 
        int col; 
        bool legalMove(int currRow, int currCol, int nextRow, int nextCol){
            if (currCol == nextCol && currRow-nextRow <= 2 && currRow-nextRow > 0){
                return true;
            }
            return false;
        }

};

class Pawn : public Piece{
    public:
        Pawn(string c, int r, int co){
            color = c;
            row = r; 
            col = co;
        }
        bool legalMove(int currRow, int currCol, int nextRow, int nextCol){
            if (currCol == nextCol && currRow-nextRow <= 2 && currRow-nextRow > 0){
                return true;
            }
            return false;
        
        }
};

class Rook : public Piece{
    public:
        Rook(string c, int r, int co){
            color = c;
            row = r; 
            col = co;
        }
        // bool legalMove(int currRow, int currCol, int nextRow, int nextCol){
        //     if (currCol == nextCol || currRow == nextRow){
        //         return true;
        //     }
        //     return false;
        
        // }
};

class Square {
    public:
        string color;
        int row;
        int col;
        Piece p;
};

