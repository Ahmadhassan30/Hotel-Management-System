#include "hotel.h"
#include <algorithm>

Hotel::Hotel(int floors, int roomsPerFloor)
    : head(nullptr), totalFloors(floors), roomsPerFloor(roomsPerFloor)
{
    initializeRooms();
}

Hotel::~Hotel()
{
    FloorNode *current = head;
    while (current)
    {
        FloorNode *next = current->next;
        for (auto room : current->rooms)
        {
            delete room;
        }
        delete current;
        current = next;
    }
}

void Hotel::initializeRooms()
{
    int roomNumber = 100;
    FloorNode *current = nullptr;

    for (int floor = 0; floor < totalFloors; floor++)
    {
        FloorNode *newFloor = new FloorNode();
        for (int room = 0; room < roomsPerFloor; room++)
        {
            Room::Type type = static_cast<Room::Type>(room % 3);
            newFloor->rooms.push_back(new Room(roomNumber++, type, Room::Status::Ready));
        }
        newFloor->next = head;
        head = newFloor;
    }
}

Room *Hotel::findAvailableRoom(Room::Type type)
{
    FloorNode *current = head;
    while (current)
    {
        for (Room *room : current->rooms)
        {
            if (room->getType() == type && room->getStatus() == Room::Status::Ready)
            {
                return room;
            }
        }
        current = current->next;
    }
    return nullptr;
}
int Hotel::getTotalFloors() const
{
    return totalFloors;
}

std::vector<Room *> Hotel::getRoomsByFloor(int floor) const
{
    std::vector<Room *> result;
    int currentFloor = 1;
    FloorNode *current = head;

    while (current && currentFloor <= floor)
    {
        if (currentFloor == floor)
        {
            return current->rooms;
        }
        current = current->next;
        currentFloor++;
    }
    return result;
}

Room *Hotel::getRoom(int roomNumber) const
{
    FloorNode *current = head;
    while (current)
    {
        for (Room *room : current->rooms)
        {
            if (room->getId() == roomNumber)
            {
                return room;
            }
        }
        current = current->next;
    }
    return nullptr;
}

void Hotel::updateRoomStatus(int roomNumber, Room::Status newStatus)
{
    if (Room *room = getRoom(roomNumber))
    {
        room->setStatus(newStatus);
    }
}