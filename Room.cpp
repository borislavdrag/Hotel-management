#include "Room.h"


//Big 4
Room::Room()
{
	this->beds = DEFAULT_BEDS;
}

Room::Room(int id, int beds)
{
	this->id = id;
	this->beds = beds;
}

Room::~Room()
{
	// no dynamic memory allocated,
	// so default destructor would do
}

Room::Room(const Room& other)
{
	copy(other);
}

Room& Room::operator=(const Room& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

// Getters
int Room::getId() const
{
	return id;
}
int Room::getBeds() const
{
	return beds;
}

// Setters
void Room::setId(int id)
{
	this->id = id;
}
void Room::setBeds(int beds)
{
	this->beds = beds;
}

//Other functions
void Room::print()
{
	std::cout << "Room " << id << " with " << beds << " beds." << std::endl;
}
void Room::free()
{
	// no dynamic memory allocated,
	// so nothing specific to free
}
void Room::copy(const Room& other)
{
	this->id = other.id;
	this->beds = other.beds;
}

