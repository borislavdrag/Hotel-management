#include "Checkin.h"

//Big 4
Checkin::Checkin()
{
    id = -1;
    from = nullptr;
    to = nullptr;
    guests = 0;
    note = nullptr;
}
Checkin::Checkin(int id, const char* from, const char* to, int guests, const char* note)
{
    this->id = id;
    if (guests < 1 || guests > DEFAULT_BEDS)
        this->guests = DEFAULT_BEDS;

    this->from = new char[strlen(from)];
    this->to = new char[strlen(to)];
    this->note = new char[strlen(note)];
    strcpy(this->from, from);
    strcpy(this->to, to);
    strcpy(this->note, note);
}
Checkin::~Checkin()
{
    if (from != nullptr)
        delete[] from;
    if (to != nullptr)
        delete[] to;
    if (note != nullptr)
        delete[] note;
}
Checkin::Checkin(const Checkin& other)
{
    free();
    copy(other);
}
Checkin& Checkin::operator=(const Checkin& other)
{
    if (this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}

//Getters
int Checkin::getId() const
{
    return this->id;
}
const char* Checkin::getFrom() const
{
    return this->from;
}
const char* Checkin::getTo() const
{
    return this->to;
}
const char* Checkin::getNote() const
{
    return this->note;
}
int Checkin::getGuests() const
{
    return this->guests;
}

//Setters
void Checkin::setId(int id)
{
    this->id = id;
}
void Checkin::setFrom(const char* from)
{
    delete[] this->from;
    this->from = new char[strlen(from) + 1];
    strcpy(this->from, from);
}
void Checkin::setTo(const char* to)
{
    delete[] this->to;
    this->to = new char[strlen(to) + 1];
    strcpy(this->to, to);
}
void Checkin::setNote(const char* note)
{
    delete[] this->note;
    this->note = new char[strlen(note) + 1];
    strcpy(this->note, note);
}
void Checkin::setGuests(int g)
{
    this->guests = g;
}

//Other functions
void Checkin::print()
{
    std::cout << "Room " << id << " from " << from << " to " << to << " for " << guests << std::endl;
}
void Checkin::free()
{
    if (from != nullptr)
        delete[] from;
    if (to != nullptr)
        delete[] to;
    if (note != nullptr)
        delete[] note;
    guests = 0;
    id = -1;
}
void Checkin::copy(const Checkin& other)
{
    this->id = other.id;
    this->guests = other.guests;

    this->from = new char[strlen(other.from) + 1];
    strcpy(this->from, other.from);
    this->to = new char[strlen(other.to) + 1];
    strcpy(this->to, other.to);
    this->note = new char[strlen(other.note) + 1];
    strcpy(this->note, other.note);
}
