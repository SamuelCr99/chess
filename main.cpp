#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace std;

void drawSquares(sf::RenderWindow& w){
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            sf::RectangleShape r(sf::Vector2f(100.f,100.f));
            r.setPosition(sf::Vector2f(float(row*100),float(col*100)));
            if ((col+row)%2){
                r.setFillColor(sf::Color::Black);
            }
            w.draw(r);
        }
    }
}

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // window.clear();
        drawSquares(window);
        window.display();
    }

    return 0;
}