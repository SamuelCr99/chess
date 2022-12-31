#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "classes.h"
#include <math.h>

using namespace std;

int addMovement(int x){
    if (x < 0){
        return x-1;
    }
    return x+1;
}

bool validPiece(Square s){
    if(s.p.color == "white" || s.p.color == "black"){
        return true;
    }
    return false;
}

bool checkLegalMove(vector <vector <Square>> sm, int currRow, int currCol, int nextRow, int nextCol, string color){
    string otherColor;
    (color == "white") ? otherColor="black" : otherColor = "white";

    if (sm[currRow][currCol].p.color != color){ //Make sure we select a piece of correct color
        return false;
    }

    if (sm[currRow][currCol].p.color == sm[nextRow][nextCol].p.color){ //Make sure to not move to square with other piece of same color
        return false;
    }

    if (sm[currRow][currCol].p.type == "pawn" && (currRow - nextRow == 1 && color == "white" || currRow - nextRow == -1 && color == "black") && abs(currCol - nextCol) == 1 && sm[nextRow][nextCol].p.color == otherColor){
        return true;
    }

    if (sm[currRow][currCol].p.type == "pawn" && sm[nextRow][nextCol].p.color == otherColor){ //Check so pawn can't take forward
        return false;
    }

    if (sm[currRow][currCol].p.type == "rook" || sm[currRow][currCol].p.type == "queen"){ //Black magic collision control 
        if (currRow == nextRow){
            int step; 
            (currCol > nextCol) ? step = -1 : step = 1;
            for (int i = currCol+step; i*step < nextCol*step; i += step){
                if (validPiece(sm[currRow][i])){
                    return false;
                }

            }
        }
        if (currCol == nextCol){
            int step; 
            (currRow > nextRow) ? step = -1 : step = 1;
            for (int i = currRow+step; i*step < nextRow*step; i += step){
                if (sm[i][currCol].p.color == "white" || sm[i][currCol].p.color == "black"){
                    return false;
                }
            }
        }
    }

    if (sm[currRow][currCol].p.type == "bishop" || sm[currRow][currCol].p.type == "queen" && abs(currRow-nextRow) == abs(currCol-nextCol)){ //Black magic collision control 
        int x_movement;
        int y_movement;
        if (nextRow > currRow){
            y_movement = 1;
        }
        else{
            y_movement = -1;
        }
        if (nextCol > currCol){
            x_movement = 1;
        }
        else{
            x_movement = -1;
        }
        while(currRow+y_movement != nextRow && currCol+x_movement != nextCol && currRow+y_movement < 8 && 
        currRow+y_movement >= 0 && currCol+x_movement < 8 && currCol+x_movement >= 0){
            if (validPiece(sm[currRow+y_movement][currCol+x_movement])){
                return false;
            }
            x_movement = addMovement(x_movement);
            y_movement = addMovement(y_movement);
        }
    }

    return sm[currRow][currCol].p.legalMove(currRow, currCol, nextRow, nextCol);
}

void drawSquares(sf::RenderWindow& w, vector<vector <Square>>& sm){
    for (vector<Square> v : sm){
        for (Square s : v){
            sf::RectangleShape r(sf::Vector2f(100.f,100.f));
            r.setPosition(sf::Vector2f(s.row*100,s.col*100));
            if (s.color == "black"){
                r.setFillColor(sf::Color(125,135,150));
            }
            w.draw(r);
        }
    }
}

void drawPieces(sf::RenderWindow& w, vector<vector<Square>> sm){
    sf::Texture t; 
    sf::Sprite Sprite;

    for (int col = 0; col < 8; col++){
        for (int row = 0; row < 8; row++){
            if (validPiece(sm[row][col])){
                string fileName = "Textures/" + sm[row][col].p.color + "_" + sm[row][col].p.type + ".png";
                t.loadFromFile(fileName);
                t.setSmooth(true);
                Sprite.setTexture(t);
                Sprite.setPosition(sm[row][col].p.col*100 + 15,sm[row][col].p.row*100 + 15);
                Sprite.setScale(0.6,0.6);
                w.draw(Sprite);
            }
        }
    }
}

void buildMatrix(vector <vector <Square>>& sm){
    for (int col = 0; col < 8; col++){
        vector<Square> r; 
        for (int row = 0; row < 8; row++){
            Square s; 
            s.col = col;
            s.row = row;
            if ((row+col)%2){
                s.color = "black";
            }
            else{
                s.color = "white";
            }
            r.push_back(s);
        }
        sm.push_back(r);
    }
}

Piece& selectPiece(vector<vector <Square>>& sm, sf::RenderWindow & w){
    sf::Vector2i mousePos = sf::Mouse::getPosition(w);
    int pressedCol = floor(mousePos.x / 100);
    int pressedRow = floor(mousePos.y / 100);
    return sm[pressedRow][pressedCol].p;
}

bool movePiece(vector<vector <Square>>& sm, sf::RenderWindow& w, Piece& p, string color){
    sf::Vector2i mousePos = sf::Mouse::getPosition(w);
    int pressedCol = floor(mousePos.x / 100);
    int pressedRow = floor(mousePos.y / 100);
    if (checkLegalMove(sm, p.row,p.col,pressedRow, pressedCol, color)){
        if (sm[pressedRow][pressedCol].p.type == "king"){
            cout << "Game over " + color + " wins" << endl;
        }

        sm[p.row][p.col].p = Piece();
        p.col = pressedCol;
        p.row = pressedRow;
        sm[pressedRow][pressedCol].p = p;
        return true;
    }
    return false;
}

void placePieces(vector <vector <Square>>& squareMatrix, string color){
    int row;
    int secondRow;
    if (color == "black"){
        row = 0;
        secondRow = 1;
    }
    else{
        row = 7;
        secondRow = 6;
    }
    squareMatrix[row][0].p = Piece (color, "rook", row, 0);
    squareMatrix[row][1].p = Piece (color, "knight", row, 1);
    squareMatrix[row][2].p = Piece (color, "bishop", row, 2);
    squareMatrix[row][3].p = Piece (color, "queen", row, 3);
    squareMatrix[row][4].p = Piece (color, "king", row, 4);
    squareMatrix[row][5].p = Piece (color, "bishop", row, 5);
    squareMatrix[row][6].p = Piece (color, "knight", row, 6);
    squareMatrix[row][7].p = Piece (color, "rook", row, 7);

    for (int i = 0; i < 8; i++){
        squareMatrix[secondRow][i].p = Piece (color, "pawn", secondRow, i);
    }

}

int main(){
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess in SFML");
    vector<vector <Square>> squareMatrix;
    buildMatrix(squareMatrix);
    placePieces(squareMatrix, "black");
    placePieces(squareMatrix, "white");
    bool selectPhase = true;
    Piece selectedPiece;
    string currentColor = "white";

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if (selectPhase){
                selectedPiece = selectPiece(squareMatrix, window);
                if (selectedPiece.color == currentColor){
                    selectPhase = false;
                }
            }
            else{
                if (movePiece(squareMatrix, window, selectedPiece, currentColor)){
                    (currentColor == "white") ? currentColor = "black" : currentColor = "white";
                    selectPhase = true;
                };
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            selectPhase = true;
        }

        drawSquares(window, squareMatrix);
        drawPieces(window, squareMatrix);
        window.display();
    }

    return 0;
}