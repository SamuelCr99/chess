#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "classes.h"
#include <math.h>

using namespace std;

void drawSquares(sf::RenderWindow& w, vector<vector <Square>>& sm){
    for (vector<Square> v : sm){
        for (Square s : v){
            sf::RectangleShape r(sf::Vector2f(100.f,100.f));
            r.setPosition(sf::Vector2f(s.row*100,s.col*100));
            if (s.color == "black"){
                r.setFillColor(sf::Color::Black);
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
            if (sm[row][col].p.color == "white"){
                t.loadFromFile("Textures/w_pawn.png");
                Sprite.setTexture(t);
                Sprite.setPosition(sm[row][col].p.col*100 + 18,sm[row][col].p.row*100 + 15);
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

void movePiece(vector<vector <Square>>& sm, sf::RenderWindow& w, Piece& p){
    sf::Vector2i mousePos = sf::Mouse::getPosition(w);
    int pressedCol = floor(mousePos.x / 100);
    int pressedRow = floor(mousePos.y / 100);
    if (p.legalMove(p.row,p.col,pressedRow, pressedCol)){
        sm[p.row][p.col].p = Piece();
        p.col = pressedCol;
        p.row = pressedRow;
        sm[pressedRow][pressedCol].p = p;
    }
}


int main(){
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess in SFML");
    vector<vector <Square>> squareMatrix;
    Pawn p("white", 6 ,1); 
    Rook r("white", 7, 0);
    buildMatrix(squareMatrix);
    squareMatrix[6][1].p = p;
    squareMatrix[7][0].p = r;
    bool selectPhase = true;
    Piece selectedPiece;

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
                if (selectedPiece.color == "white" || selectedPiece.color == "black"){
                    selectPhase = false;
                }
            }
            else{
                movePiece(squareMatrix, window, selectedPiece);
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