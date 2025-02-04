#include "hotel_view.h"
#include <iostream>

HotelView::HotelView(Hotel &hotel) : hotel(hotel)
{
    if (!font.loadFromFile("media/Chivo-Bold.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("media/galaxy.jpg"))
    {
        std::cerr << "Error loading background image!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void HotelView::draw(sf::RenderWindow &window)
{
    // Scale the background to cover the entire window
    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Draw the background first
    window.draw(backgroundSprite);

    int totalFloors = hotel.getTotalFloors();

    const float roomWidth = 80.f;
    const float roomHeight = 60.f;
    const float spacing = 10.f;

    for (int floor = 1; floor <= totalFloors; ++floor)
    {
        std::vector<Room *> rooms = hotel.getRoomsByFloor(floor);
        float yPosition = 100.f + (floor - 1) * (roomHeight + spacing);

        for (size_t i = 0; i < rooms.size(); ++i)
        {
            Room *room = rooms[i];

            sf::RectangleShape roomShape(sf::Vector2f(roomWidth, roomHeight));
            roomShape.setPosition(200.f + i * (roomWidth + spacing), yPosition);
            roomShape.setOutlineThickness(2.f);
            roomShape.setOutlineColor(sf::Color::White);
            roomShape.setFillColor(getRoomColor(room->getStatus()));

            window.draw(roomShape);

            sf::Text roomNumberText(std::to_string(room->getId()), font, 18);
            roomNumberText.setFillColor(sf::Color::White);
            roomNumberText.setPosition(roomShape.getPosition().x + 20, roomShape.getPosition().y + 15);
            window.draw(roomNumberText);
        }
    }
}

sf::Color HotelView::getRoomColor(Room::Status status)
{
    switch (status)
    {
    case Room::Status::Ready:
        return sf::Color(100, 255, 100);
    case Room::Status::Occupied:
        return sf::Color(255, 50, 50);

    default:
        return sf::Color(150, 150, 150);
    }
}
