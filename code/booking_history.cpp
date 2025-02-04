#include "booking_history.h"
#include <iostream>
using namespace std;
void BookingHistory::push(const BookingRecord &record)
{
    history.push(record);
    cout << "                    |Booking recorded: Room " << record.roomNumber
         << " for " << record.nights << " nights|           \n";
}

BookingRecord BookingHistory::pop()
{
    if (!history.empty())
    {
        auto top = history.top();
        history.pop();
        return top;
    }
    return {};
}

BookingRecord BookingHistory::peek() const
{
    if (!history.empty())
        return history.top();
    return {};
}

bool BookingHistory::isEmpty() const
{
    return history.empty();
}

void BookingHistory::clear()
{
    while (!history.empty())
        history.pop();
}

void BookingHistory::display() const
{
    if (history.empty())
    {
        std::cout << "\n '''History not available.''' \n";
        return;
    }

    stack<BookingRecord> temp = history;
    cout << "\n                    ----------BOOKING HISTORY----------\n";
    while (!temp.empty())
    {
        BookingRecord record = temp.top();
        cout << "\nRoom " << record.roomNumber << " | Customer: "
             << record.customerName << " | Nights: " << record.nights << "\n";
        temp.pop();
    }
}
