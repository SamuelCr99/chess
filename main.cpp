#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "classes.h"

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

void drawPieces(sf::RenderWindow& w, Pawn& p){
    sf::Texture t; 
    t.loadFromFile("Textures/w_pawn.png");
    sf::Sprite Sprite(t);
    Sprite.setPosition(p.col*100 + 20,p.row*100 + 15);
    Sprite.setScale(0.6,0.6);
    w.draw(Sprite);
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


int main(){
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess in SFML");
    vector<vector <Square>> squareMatrix;
    Pawn p("white", 6 ,1); 
    buildMatrix(squareMatrix);


    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        drawSquares(window, squareMatrix);
        drawPieces(window, p);
        window.display();
    }

    return 0;
}