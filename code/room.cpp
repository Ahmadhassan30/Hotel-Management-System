#include "room.h"
#include <iostream>
using namespace std;

Room::Room(int id, Type type, Status status)
    : id(id), type(type), status(status) {}

int Room::getId() const { return id; }
Room::Type Room::getType() const { return type; }
Room::Status Room::getStatus() const { return status; }
void Room::setStatus(Status newStatus) { status = newStatus; }

string Room::toString() const
{
    string typeStr = (type == Type::Single) ? "Single" : (type == Type::Double) ? "Double"
                                                                                : "Suite";
    string statusStr = (status == Status::Occupied) ? "Occupied" : (status == Status::Booked) ? "Booked"
                                                                                              : "Ready";
    return "Room " + std::to_string(id) + " [" + typeStr + " | " + statusStr + "]";
}
