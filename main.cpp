#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(5.f);
    shape.setFillColor(sf::Color::Blue);
    int dir = 1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        shape.setPosition(shape.getPosition().x+dir,5);
        if (shape.getPosition().x > 195 || shape.getPosition().x < 0){
            dir *= -1;
        }
        window.clear();
        window.draw(shape);
        window.display();
        for (int i = 0; i < 5000000; i++);

    }

    return 0;
}