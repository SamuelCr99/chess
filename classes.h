#include <string>

using namespace std;

class Piece {
    public: 
        string color;
        int row; 
        int col; 
};

class Pawn : public Piece{
    public:
        Pawn(string c, int r, int co){
            color = c;
            row = r; 
            col = co;
        }
};

class Square {
    public:
        string color;
        int row;
        int col;
        Piece p;
};

