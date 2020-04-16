#include <SFML/Graphics.hpp>
sf::Font font;

int main()
{
    font.loadFromFile("fonts/thestrong.ttf");
    sf::Text text;

// select the font
text.setFont(font); // font is a sf::Font

// set the string to display
text.setString("You are attacked by an unarmed goblin!");

// set the character size
text.setCharacterSize(24); // in pixels, not points!

// set the color
text.setFillColor(sf::Color::Red);

// set the text style
text.setStyle(sf::Text::Bold | sf::Text::Underlined);
text.setPosition(sf::Vector2f(100.f, 500.f));


sf::Texture texture, ch1t, ch2t, ch3t, ch4t;
    texture.loadFromFile("Gob.png");
    sf::Sprite sprite;
sprite.setTexture(texture);
    ch1t.loadFromFile("pics/ch1.png");
    sf::Sprite ch1;
ch1.setTexture(ch1t);
ch1.setPosition(sf::Vector2f(900.f, 100.f));
ch1.setScale(sf::Vector2f(0.75f, 0.75f));
    ch2t.loadFromFile("pics/ch2.png");
    sf::Sprite ch2;
ch2.setTexture(ch2t);
ch2.setPosition(sf::Vector2f(900.f, 250.f));
ch2.setScale(sf::Vector2f(0.75f, 0.75f));
    ch3t.loadFromFile("pics/ch3.png");
    sf::Sprite ch3;
ch3.setTexture(ch3t);
ch3.setPosition(sf::Vector2f(900.f, 400.f));
ch3.setScale(sf::Vector2f(0.75f, 0.75f));

    ch4t.loadFromFile("pics/ch4.png");
    sf::Sprite ch4;
ch4.setTexture(ch4t);
ch4.setPosition(sf::Vector2f(900.f, 550.f));
ch4.setScale(sf::Vector2f(0.75f, 0.75f));

    sf::RenderWindow window(sf::VideoMode(1200, 700), "SFML works!");


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
window.draw(sprite);
window.draw(ch1);
window.draw(ch2);
window.draw(ch3);
window.draw(ch4);
window.draw(text);

        window.display();
    }

    return 0;
}