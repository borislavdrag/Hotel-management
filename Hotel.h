#include "Checkin.h"
#include "Repair.h"

#define CAPACITY 20

class Hotel
{
	int nRepairs;
	int nCheckIns;
	Room* rooms;
	Checkin* checkIns;
	Repair* repairs;

public:

	Hotel();
	~Hotel();
	Hotel(const Hotel&);
	Hotel& operator=(const Hotel&);

	void report(const char*, const char*) const;
	void available(const char*, const char*) const;
	Room& getRoom(int id);

	void checkin(int, const char*, const char*, int, const char* = "");
	void repair(int, const char*, const char*, const char* = "");

	void print();
	void free();
	void copy(const Hotel&);

	bool load(std::fstream&);
	bool save(std::fstream&);
};
