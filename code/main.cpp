#include <SFML/Graphics.hpp>
#include "hotel.h"
#include "booking_queue.h"
#include "booking_history.h"
#include "hotel_view.h"
#include "button.h"
#include <iostream>
#include <string>
using namespace std;

enum class AppState
{
    Start,
    HotelView
};

// Function to handle the start screen
void handleStartWindow(sf::RenderWindow &window, AppState &state, Button &btnStart, Button &btnExit, const sf::Font &lobsterFont, const sf::Font &chivoFont)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (btnStart.isMouseOver(window))
            {
                state = AppState::HotelView;
            }
            else if (btnExit.isMouseOver(window))
            {
                window.close();
            }
        }
    }

    // Loading background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("media/main.jpg"))
    {
        std::cerr << "Error loading background image!" << std::endl;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    // Scaling background to fit window
    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    // title text
    sf::Text title("GALAXY HOTEL", lobsterFont, 80);
    title.setFillColor(sf::Color::Cyan);
    title.setOutlineColor(sf::Color::Blue);
    title.setOutlineThickness(2);
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        (window.getSize().x - title.getLocalBounds().width) / 2,
        100);

    // Faded effect beneath title
    sf::RectangleShape fadedTitleBackground(sf::Vector2f(title.getLocalBounds().width + 40, title.getLocalBounds().height + 20));
    fadedTitleBackground.setFillColor(sf::Color(0, 0, 0, 150));
    fadedTitleBackground.setPosition(title.getPosition().x - 20, title.getPosition().y - 10);

    // footer text
    sf::Text footer("Design and code by Ahmad Hassan", chivoFont, 20);
    footer.setFillColor(sf::Color::White);
    footer.setOutlineColor(sf::Color(150, 150, 150, 200));
    footer.setOutlineThickness(1);
    footer.setPosition(
        window.getSize().x - footer.getLocalBounds().width - 20, // 20 is the margin from the right
        window.getSize().y - footer.getLocalBounds().height - 10 // 10 is the margin from the bottom
    );

    // Faded effect beneath footer
    sf::RectangleShape fadedFooterBackground(sf::Vector2f(footer.getLocalBounds().width + 30, footer.getLocalBounds().height + 10));
    fadedFooterBackground.setFillColor(sf::Color(0, 0, 0, 150));
    fadedFooterBackground.setPosition(footer.getPosition().x - 15, footer.getPosition().y - 5);

    // Update and draw buttons
    btnStart.update(window);
    btnExit.update(window);

    // Render everything
    window.clear();
    window.draw(backgroundSprite);
    window.draw(fadedTitleBackground);
    window.draw(title);
    window.draw(fadedFooterBackground);
    window.draw(footer);
    btnStart.draw(window);
    btnExit.draw(window);
    window.display();
}

// Function for booking a room via terminal input.
void bookRoomTerminalInput(Hotel &hotel, BookingQueue &bookingQueue, BookingHistory &bookingHistory)
{
    string customerName;
    string roomTypeStr;
    int nights;
    Room::Type roomType;

    cout << "\n                    ------------------BOOKING FORM------------------\n";
    cout << "\nEnter your name: ";
    getline(cin, customerName);

    cout << "Enter room type (Single, Double, Suite): ";
    getline(std::cin, roomTypeStr);

    // Handle room type input
    if (roomTypeStr == "Single")
        roomType = Room::Type::Single;
    else if (roomTypeStr == "Suite")
        roomType = Room::Type::Suite;
    else if (roomTypeStr == "Double")
        roomType = Room::Type::Double;
    else
    {
        cout << " '''Oops! Invalid type.''' " << std::endl;
        return;
    }

    cout << "Enter number of nights: ";
    cin >> nights;
    cin.ignore();

    // Finding an available room based on the selected room type
    Room *roomToBook = hotel.findAvailableRoom(roomType);
    if (roomToBook)
    {
        hotel.updateRoomStatus(roomToBook->getId(), Room::Status::Occupied);
        BookingRequest request = {customerName, roomToBook->getId(), nights};
        bookingQueue.enqueue(request);
        BookingRecord record = {roomToBook->getId(), customerName, nights, roomToBook->getStatus()};
        bookingHistory.push(record);
    }
    else
    {
        std::cout << " '''No available rooms of the requested type! ''' " << endl;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Galaxy Hotel");

    Hotel hotel(5, 10);
    BookingQueue bookingQueue;
    BookingHistory bookingHistory;
    HotelView hotelView(hotel);

    // Load fonts
    sf::Font lobsterFont;
    if (!lobsterFont.loadFromFile("media/Lobster-Regular.ttf"))
    {
        std::cerr << "Error loading Lobster font!" << std::endl;
        return 1;
    }

    sf::Font chivoFont;
    if (!chivoFont.loadFromFile("media/Chivo-Bold.ttf"))
    {
        std::cerr << "Error loading Chivo-Bold font!" << std::endl;
        return 1;
    }

    // Aligning buttons for the start screen
    float startButtonX = (1280 - 200) / 2; // Center horizontally (200 is button width)
    float startButtonY = 400;              // Position vertically
    float startButtonSpacing = 20.0f;      // Space between buttons

    Button btnStart(startButtonX, startButtonY, "Start", chivoFont);
    Button btnExit(startButtonX, startButtonY + btnStart.getShape().getSize().y + startButtonSpacing, "Exit", chivoFont);

    // Fixed the size for all buttons.
    float buttonWidth = 250;
    float buttonHeight = 50;

    // Center horizontally and position vertically just below the floors and rooms
    float hotelButtonX = (window.getSize().x - buttonWidth) / 2; // Center horizontally
    float hotelButtonY = window.getSize().y - 200;               // Position near the bottom (adjust as needed)
    float hotelButtonSpacing = 20.0f;                            // Space between buttons

    // Creating buttons with a fixed size
    Button btnBook(hotelButtonX, hotelButtonY, "Book Room", chivoFont);
    btnBook.setSize(buttonWidth, buttonHeight); // Set button size

    Button btnCancel(hotelButtonX, hotelButtonY + btnBook.getShape().getSize().y + hotelButtonSpacing, "Cancel Booking", chivoFont);
    btnCancel.setSize(buttonWidth, buttonHeight); // Set button size

    Button btnViewHistory(hotelButtonX, hotelButtonY + btnBook.getShape().getSize().y * 2 + hotelButtonSpacing * 2, "View History", chivoFont);
    btnViewHistory.setSize(buttonWidth, buttonHeight); // Set button size

    AppState state = AppState::Start;

    while (window.isOpen())
    {
        if (state == AppState::Start)
        {
            handleStartWindow(window, state, btnStart, btnExit, lobsterFont, chivoFont);
        }
        else if (state == AppState::HotelView)

        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (btnBook.isMouseOver(window))
                    {
                        bookRoomTerminalInput(hotel, bookingQueue, bookingHistory);
                    }
                    else if (btnCancel.isMouseOver(window))
                    {
                        if (!bookingQueue.isEmpty())
                        {
                            BookingRequest request = bookingQueue.dequeue();
                            Room *roomToCancel = hotel.getRoom(request.roomNumber);

                            if (roomToCancel)
                            {
                                hotel.updateRoomStatus(roomToCancel->getId(), Room::Status::Ready);
                                bookingHistory.pop();
                            }
                        }
                        else
                        {
                            std::cout << "No bookings to cancel!" << std::endl;
                         }
                    }
                    else if (btnViewHistory.isMouseOver(window))
                    {
                        bookingHistory.display();
                    }
                }
            }

            btnBook.update(window);
            btnCancel.update(window);
            btnViewHistory.update(window);

            window.clear(sf::Color(25, 25, 25));
            hotelView.draw(window);
            btnBook.draw(window);
            btnCancel.draw(window);
            btnViewHistory.draw(window);
            window.display();
        }
    }

    return 0;
}
