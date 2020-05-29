#include "Room.h"

class Checkin
{
	int id;
	char* from;
	char* to;
	char* note;
	int guests;
	int days;

public:
	Checkin();
	Checkin(int, const char*, const char*, int, const char* = "");
	~Checkin();
	Checkin(const Checkin&);
	Checkin& operator= (const Checkin&);

	int getId() const;
	const char* getFrom() const;
	const char* getTo() const;
	const char* getNote() const;
	int getGuests() const;

	void setId(int);
	void setFrom(const char*);
	void setTo(const char*);
	void setNote(const char*);
	void setGuests(int);

	bool intersect(const Checkin&);
	void print();
	void copy(const Checkin&);
	void free();
};

