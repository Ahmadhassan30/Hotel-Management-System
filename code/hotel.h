#pragma once
#include "room.h"
#include <vector>
#include <stdexcept>
using namespace std;

class Hotel
{
public:
    Hotel(int floors, int roomsPerFloor);
    ~Hotel();

    int getTotalFloors() const;
    Room *findAvailableRoom(Room::Type type);
    Room *getRoom(int roomNumber) const;
    void updateRoomStatus(int roomNumber, Room::Status newStatus);
    vector<Room *> getRoomsByType(Room::Type type) const;
    vector<Room *> getRoomsByFloor(int floor) const;

private:
    struct FloorNode
    {
        vector<Room *> rooms;
        FloorNode *next;
    };

    FloorNode *head;
    int totalFloors;
    int roomsPerFloor;

    void initializeRooms();
};