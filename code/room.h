#pragma once
#include <string>

class Room
{
public:
    enum class Type
    {
        Single,
        Double,
        Suite
    };

    enum class Status
    {
        Occupied,
        Booked,
        Ready
    };

    Room(int id, Type type, Status status);
    int getId() const;
    Type getType() const;
    Status getStatus() const;
    void setStatus(Status newStatus);
    std::string toString() const; // Added for debugging

private:
    int id;
    Type type;
    Status status;
};
