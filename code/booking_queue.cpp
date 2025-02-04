#include "booking_queue.h"
#include <iostream>
using namespace std;

void BookingQueue::enqueue(const BookingRequest &request)
{
    // Enqueue the booking request
    bookingQueue.push(request);

    // Push the request to cancel stack for potential cancellation
    cancelStack.push(request);

    cout << "\n                    |Room " << request.roomNumber << " booked for " << request.nights << " nights by "
         << request.customerName << "|\n";
}

BookingRequest BookingQueue::dequeue()
{
    if (!cancelStack.empty())
    {
        // Cancel the last booking
        BookingRequest lastBooking = cancelStack.top();
        cancelStack.pop();

        std::cout << "\n                    |Room " << lastBooking.roomNumber << " booking canceled for " << lastBooking.customerName << "|\n";
        return lastBooking;
    }

    std::cout << "\n '''No bookings to cancel.''' \n";
    return {};
}

bool BookingQueue::isEmpty() const
{
    return bookingQueue.empty();
}

BookingRequest BookingQueue::peek() const
{
    if (!bookingQueue.empty())
        return bookingQueue.front();
    return {};
}
