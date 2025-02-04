#include "button.h"
#include <SFML/Graphics.hpp>

Button::Button(float x, float y, const std::string &text, const sf::Font &font)
{
    this->text.setString(text);
    this->text.setFont(font);
    this->text.setCharacterSize(28);
    this->text.setFillColor(sf::Color::White);

    shape.setSize(sf::Vector2f(280, 60)); // Default size
    shape.setFillColor(normalColor);
    shape.setPosition(x, y);

    alignText();
}

void Button::setSize(float width, float height)
{
    shape.setSize(sf::Vector2f(width, height));
    alignText(); // Re-align text after resizing
}

void Button::setFontSize(unsigned int size)
{
    text.setCharacterSize(size);
    alignText(); // Re-align text after font size change
}

void Button::setBackgroundColor(const sf::Color &color)
{
    normalColor = color;
    shape.setFillColor(normalColor);
}

void Button::setHoverColor(const sf::Color &color)
{
    hoverColor = color;
}

void Button::setTextColor(const sf::Color &color)
{
    text.setFillColor(color);
}

void Button::draw(sf::RenderWindow &window) const
{
    window.draw(shape);
    window.draw(text);
}

bool Button::isMouseOver(const sf::RenderWindow &window) const
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::update(const sf::RenderWindow &window)
{
    if (isMouseOver(window))
        shape.setFillColor(hoverColor);
    else
        shape.setFillColor(normalColor);
}

void Button::alignText()
{
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text.setPosition(
        shape.getPosition().x + shape.getSize().x / 2,
        shape.getPosition().y + shape.getSize().y / 2);
}
