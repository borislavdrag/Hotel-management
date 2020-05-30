#include "Hotel.h"

//Helper functions
int countLeapYears(const char* d)
{
	char year[4];
	char month[2];
	strncpy(year, d, 4);
	strncpy(month, d + 5, 2);

	int years = atoi(year);
	if (atoi(month) <= 2)
		years--;

	return years / 4 - years / 100 + years / 400;
}
int getDifference(const char* a, const char* b)
{
	char yearA[4];
	char yearB[4];
	char monthA[2];
	char monthB[2];
	char dateA[2];
	char dateB[2];
	strncpy(yearA, a, 4);
	strncpy(yearB, b, 4);
	strncpy(monthA, a + 5, 2);
	strncpy(monthB, b + 5, 2);
	strncpy(dateA, a + 8, 2);
	strncpy(dateB, b + 8, 2);

	int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	int n1 = atoi(yearA) * 365 + atoi(dateA);

	// Add days for months in given date 
	for (int i = 0; i < atoi(monthA) - 1; i++)
		n1 += monthDays[i];

	// Since every leap year is of 366 days, 
	// Add a day for every leap year 
	n1 += countLeapYears(a);

	// SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2' 

	long int n2 = atoi(yearB) * 365 + atoi(dateB);
	for (int i = 0; i < atoi(monthB) - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYears(b);

	// return difference between two counts 
	if (n2 - n1 >= 1)
		return (n2 - n1 + 1);
	else
		return 0;
}
int compareDates(const char* a, const char* b)
{
	char yearA[4];
	char yearB[4];
	char monthA[2];
	char monthB[2];
	char dateA[2];
	char dateB[2];

	strncpy(yearA, a, 4);
	strncpy(yearB, b, 4);
	strncpy(monthA, a+5, 2);
	strncpy(monthB, b+5, 2);
	strncpy(dateA, a+8, 2);
	strncpy(dateB, b+8, 2);

	if (atoi(yearA) > atoi(yearB))
		return -1;
	else if (atoi(yearA) < atoi(yearB))
		return 1;
	else
	{
		if (atoi(monthA) > atoi(monthB))
			return -1;
		else if (atoi(monthA) < atoi(monthB))
			return 1;
		else
		{
			if (atoi(dateA) > atoi(dateB))
				return -1;
			else if (atoi(dateA) < atoi(dateB))
				return 1;
			else
				return 0;
		}
	}
}

//Big 4
Hotel::Hotel()
{
	int nRepairs = 0;
	int nCheckIns = 0;
	this->rooms = new Room[CAPACITY];
	for (int i = 0; i < CAPACITY; i++)
		this->rooms[i].setId(100*(i/10 + 1) + i%10); // ids are set arbitrarily
	this->repairs = nullptr;
	this->checkIns = nullptr;
}
Hotel::~Hotel()
{
	if (repairs != nullptr)
		delete[] repairs;
	if (checkIns != nullptr)
		delete[] checkIns;
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
	int roomUsed[CAPACITY] = {0};
	for (int i = 0; i < nCheckIns; i++)
	{
		int properId = checkIns[i].getId();
		int simpleId = 10 * (properId / 100 - 1) + properId % 100;
		if (compareDates(from, checkIns[i].getFrom()) >= 0 &&
			compareDates(to, checkIns[i].getTo()) <= 0)
		{
			roomUsed[simpleId] += getDifference(checkIns[i].getFrom(), checkIns[i].getTo());
		}

		else if (compareDates(from, checkIns[i].getFrom()) >= 0 &&
			compareDates(to, checkIns[i].getTo()) > 0)
		{
			roomUsed[simpleId] += getDifference(checkIns[i].getFrom(), to);
		}
		else if (compareDates(from, checkIns[i].getFrom()) < 0 &&
			compareDates(to, checkIns[i].getTo()) <= 0)
		{
			roomUsed[simpleId] += getDifference(from, checkIns[i].getTo());
		}
		else
			roomUsed[simpleId] += getDifference(from, to);
	}

	for (int i = 0; i < CAPACITY; i++)
	{
		if (roomUsed[i] > 0)
			std::cout << "Room " << 100 * (i / 10 + 1) + i % 10 << 
			" has been used for " << roomUsed[i] << " days." << std::endl;
	}
}
void Hotel::available(const char* from, const char* to, int beds) const
{
	int roomsAvailable[CAPACITY] = {};

	for (int i = 0; i < nRepairs; i++)
	{
		int properId = repairs[i].getId();
		int simpleId = 10 * (properId / 100 - 1) + properId % 100;
		if (!(compareDates(from, repairs[i].getTo()) < 0 || compareDates(to, repairs[i].getFrom()) > 0))
		{
			roomsAvailable[simpleId] = 1;
		}
	}
	for (int i = 0; i < nCheckIns; i++)
	{
		int properId = checkIns[i].getId();
		int simpleId = 10*(properId / 100 - 1) + properId % 100;
		if (!(compareDates(from, checkIns[i].getTo()) < 0 || compareDates(to, checkIns[i].getFrom()) > 0))
		{
			roomsAvailable[simpleId] = 1;
		}
	}
	for (int i = 0; i < CAPACITY; i++)
		if(roomsAvailable[i] == 0 && rooms[i].getBeds() >= beds)
			std::cout << "Room " << 100 * (i / 10 + 1) + i % 10 <<
			" is free with " << rooms[i].getBeds() << " beds." << std::endl;
}
void Hotel::available(const char* date) const
{
	available(date, date, 0);
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
	if (this->checkIns == nullptr)
		this->checkIns = new Checkin[1];
	else
	{
		Checkin* temp = new Checkin[nCheckIns + 1];
		for (int i = 0; i < nCheckIns; i++)
			temp[i] = this->checkIns[i];
		delete[] this->checkIns;
		this->checkIns = temp;
	}
	checkIns[nCheckIns].setId(id);
	checkIns[nCheckIns].setFrom(from);
	checkIns[nCheckIns].setTo(to);
	checkIns[nCheckIns].setNote(note);
	if (guests == -1)
		checkIns[nCheckIns].setGuests(getRoom(id).getBeds());
	else
		checkIns[nCheckIns].setGuests(guests);

	nCheckIns++;
}
void Hotel::repair(int id, const char* from, const char* to, const char* note)
{
	if (this->repairs == nullptr)
		this->repairs = new Repair[1];
	else
	{
		Repair* temp = new Repair[nRepairs + 1];
		for (int i = 0; i < nRepairs; i++)
			temp[i] = this->repairs[i];
		delete[] this->repairs;
		this->repairs = temp;
	}
	repairs[nRepairs].setId(id);
	repairs[nRepairs].setFrom(from);
	repairs[nRepairs].setTo(to);
	repairs[nRepairs].setNote(note);

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

	checkIns = new Checkin[other.nCheckIns];
	nCheckIns = other.nCheckIns;
	for (int i = 0; i < nCheckIns; i++)
		checkIns[i] = other.checkIns[i];

	repairs = new Repair[other.nRepairs];
	nRepairs = other.nRepairs;
	for (int i = 0; i < nRepairs; i++)
		repairs[i] = other.repairs[i];
}
void Hotel::free()
{
	if (repairs != nullptr)
		delete[] repairs;
	if (checkIns != nullptr)
		delete[] checkIns;
	delete[] rooms;
}
bool Hotel::save(std::fstream& out)
{
	if (!out.good())
		return 0;
	
	out << nCheckIns << ' ' << nRepairs << '\n';
	for (int i = 0; i < CAPACITY; i++)
		out << rooms[i].getId() << ' ' << rooms[i].getBeds() << '\n';
	for (int i = 0; i < nCheckIns; i++)
	{
		out << checkIns[i].getId() << ' ';
		out << checkIns[i].getGuests() << ' ';
		out << checkIns[i].getFrom() << ' ';
		out << checkIns[i].getTo() << ' ';
		out << checkIns[i].getNote() << '\n';
	}
	for (int i = 0; i < nRepairs; i++)
	{
		out << repairs[i].getId() << ' ';
		out << repairs[i].getFrom() << ' ';
		out << repairs[i].getTo() << ' ';
		out << repairs[i].getNote() << '\n';
	}

	return 1;
}
bool Hotel::load(std::fstream& in)
{
	return 1;
}