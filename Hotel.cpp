#include "Hotel.h"

//Helper functions
int compareDates(const char* a, const char* b)
{

	return 0;
}

//Big 4
Hotel::Hotel()
{
	int nRepairs = 0;
	int nCheckIns = 0;
	this->rooms = new Room[CAPACITY];
	for (int i = 0; i < CAPACITY; i++)
		this->rooms[i].setId(100*(i/10 + 1) + i%10); // ids are set arbitraily
	this->repairs = nullptr;
	this->checkIns = nullptr;
}
Hotel::~Hotel()
{
	/*if (repairs != nullptr)
		delete[] repairs;
	if (checkIns != nullptr)
		delete[] checkIns;*/
	delete[] rooms;
}
Hotel::Hotel(const Hotel& other)
{
	free();
	copy(other);
}
Hotel& Hotel::operator=(const Hotel& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

//"Getters"
void Hotel::report(const char* from, const char* to) const
{

}
void Hotel::available(const char* from, const char* to) const
{

}
Room& Hotel::getRoom(int id)
{
	for (int i = 0; i < CAPACITY; i++)
		if (rooms[i].getId() == id)
			return rooms[i];
	std::cout << "No such room found!" << std::endl;
}

//"Setters"
void Hotel::checkin(int id, const char* from, const char* to, int guests, const char* note)
{
	nCheckIns++;
}
void Hotel::repair(int id, const char* from, const char* to, const char* note)
{
	nRepairs++;
}

//Other functions
void Hotel::print()
{
	std::cout << "The hotel has " << CAPACITY << " rooms:" << std::endl;
	for (int i = 0; i < CAPACITY; i++)
		rooms[i].print();
}
void Hotel::copy(const Hotel& other)
{
	rooms = new Room[CAPACITY];
	for (int i = 0; i < CAPACITY; i++)
		rooms[i] = other.rooms[i];

	/*checkIns = new Checkin[other.nCheckIns];
	nCheckIns = other.nCheckIns;
	for (int i = 0; i < nCheckIns; i++)
		checkIns[i] = other.checkIns[i];

	repairs = new Repair[other.nRepairs];
	nRepairs = other.nRepairs;
	for (int i = 0; i < nRepairs; i++)
		repairs[i] = other.repairs[i]*/;
}
void Hotel::free()
{
	/*if (repairs != nullptr)
		delete[] repairs;
	if (checkIns != nullptr)
		delete[] checkIns;*/
	delete[] rooms;
}
bool Hotel::save(std::fstream& out)
{
	return 1;
}
bool Hotel::load(std::fstream& in)
{
	return 1;
}