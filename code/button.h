#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
    Button(float x, float y, const std::string &text, const sf::Font &font);

    void draw(sf::RenderWindow &window) const;
    bool isMouseOver(const sf::RenderWindow &window) const;
    void update(const sf::RenderWindow &window);

    void setSize(float width, float height);
    void setFontSize(unsigned int size);
    void setBackgroundColor(const sf::Color &color);
    void setHoverColor(const sf::Color &color);
    void setTextColor(const sf::Color &color);

    sf::RectangleShape getShape() const { return shape; }

private:
    void alignText(); // Private helper function to align text within the button

    sf::RectangleShape shape;
    sf::Text text;
    sf::Color normalColor = sf::Color(0, 100, 255); // Default color (Deep Blue)
    sf::Color hoverColor = sf::Color(0, 150, 255);  // Hover color (Brighter Blue)
};
