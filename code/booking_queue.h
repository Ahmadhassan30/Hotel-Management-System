#pragma once
#include <queue>
#include <stack>
#include <string>
#include "room.h"
using namespace std;

struct BookingRequest
{
    string customerName;
    int roomNumber;
    int nights;
};

class BookingQueue
{
public:
    void enqueue(const BookingRequest &request); // Book rooms sequentially
    BookingRequest dequeue();                    // Cancel last booking first
    bool isEmpty() const;
    BookingRequest peek() const; // View next booking

private:
    queue<BookingRequest> bookingQueue; // Sequential queue for bookings
    stack<BookingRequest> cancelStack;  // Stack for reverse cancellations
};
