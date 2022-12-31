#include <string>

using namespace std;

class Piece {
    public: 
        string color;
        string type;
        int row; 
        int col; 
        bool selected;

        Piece (){
        }
        Piece(string c, string t, int r, int co){
            color = c;
            type = t;
            row = r; 
            col = co;
            selected = false;
        }

        bool legalMove(int currRow, int currCol, int nextRow, int nextCol){
            if (type == "pawn"){
                if (currCol == nextCol && abs(currRow-nextRow) <= 1 && ((color == "white" && currRow > nextRow) || (color == "black" && currRow < nextRow))){
                    return true;
                }
                if (currCol == nextCol && abs(currRow-nextRow) <= 2 && ((color == "black" && row == 1) || (color == "white" && row == 6))){
                    return true;
                }
            }

            if (type == "rook" || type == "queen"){ 
                if(currCol == nextCol || currRow == nextRow){
                    return true;
                }
            }

            if (type == "bishop" || type == "queen"){
                if (abs(currRow - nextRow) == abs(currCol - nextCol)){
                    return true;
                }
            }

            if (type == "king"){
                if (currRow == nextRow && abs(currCol - nextCol) == 1 || currCol == nextCol && abs(currRow - nextRow) == 1){
                    return true;
                }
            }
            
            if (type == "knight"){
                if (abs(currRow - nextRow) == 1 && abs(currCol - nextCol) == 2 || abs(currRow - nextRow) == 2 && abs(currCol - nextCol) == 1){
                    return true;
                }
            }

            return false;
        
        }
};

class Square {
    public:
        string color;
        int row;
        int col;
        Piece p;
};