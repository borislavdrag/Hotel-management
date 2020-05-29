#include "Room.h"

class Repair
{
	int id;
	char* from;
	char* to;
	char* note;

public:
	Repair();
	Repair(int, const char*, const char*, const char*);
	~Repair();
	Repair(const Repair&);
	Repair& operator=(const Repair&);

	int getId() const;
	const char* getFrom() const;
	const char* getTo() const;
	const char* getNote() const;

	void setId(int);
	void setFrom(const char*);
	void setTo(const char*);
	void setNote(const char*);

	bool intersect(const Repair&);
	void print();
	void free();
	void copy(const Repair&);
};

