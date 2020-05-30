#ifndef ROOM
#define ROOM

#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>

#define DEFAULT_BEDS 2

class Room
{
	int id;
	int beds;

public:

	Room();
	Room(int, int = DEFAULT_BEDS);
	~Room();;
	Room(const Room&);
	Room& operator=(const Room&);

	int getId() const;
	int getBeds() const;

	void setId(int);
	void setBeds(int);

	void print();
	void copy(const Room&);
	void free();
};

#endif