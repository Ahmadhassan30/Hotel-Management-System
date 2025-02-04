#pragma once
#include <stack>
#include <iostream>
#include "room.h"
using namespace std;
struct BookingRecord
{
    int roomNumber;
    string customerName;
    int nights;
    Room::Status previousStatus;
};

class BookingHistory
{
public:
    void push(const BookingRecord &record);
    BookingRecord pop();
    BookingRecord peek() const; // View last record without removing
    void display() const;       // Show history
    void clear();               // Clear history
    bool isEmpty() const;

private:
    stack<BookingRecord> history;
};
