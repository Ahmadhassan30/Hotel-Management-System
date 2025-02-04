#pragma once
#include <SFML/Graphics.hpp>
#include "hotel.h"

class HotelView
{
public:
    HotelView(Hotel &hotel);                     // Only pass hotel reference
    void draw(sf::RenderWindow &window);         // Draw the hotel and rooms
    sf::Color getRoomColor(Room::Status status); // Get color based on room status

private:
    Hotel &hotel;                  // Reference to the Hotel object
    sf::Font font;                 // Font for displaying text
    sf::Texture backgroundTexture; // Background texture
    sf::Sprite backgroundSprite;   // Background sprite for the window
};
