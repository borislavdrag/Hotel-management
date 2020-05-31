#include "Repair.h"

//Big 4
Repair::Repair()
{
    id = -1;
    from = nullptr;
    to = nullptr;
    note = nullptr;
}
Repair::Repair(int id, const char* from, const char* to, const char* note = "")
{
    this->id = id;

    this->from = new char[strlen(from)+1];
    this->to = new char[strlen(to)+1];
    this->note = new char[strlen(note)+1];
    strcpy(this->from, from);
    strcpy(this->to, to);
    strcpy(this->note, note);
}
Repair::~Repair()
{
    if (from != nullptr)
        delete[] from;
    if (to != nullptr)
        delete[] to;
    if (note != nullptr)
        delete[] note;
}
Repair::Repair(const Repair& other)
{
    free();
    copy(other);
}
Repair& Repair::operator=(const Repair& other)
{
    if (this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}

//Getters
int Repair::getId() const
{
    return this->id;
}
const char* Repair::getFrom() const
{
    return this->from;
}
const char* Repair::getTo() const
{
    return this->to;
}
const char* Repair::getNote() const
{
    return this->note;
}

//Setters
void Repair::setId(int id)
{
    this->id = id;
}
void Repair::setFrom(const char* from)
{
    delete[] this->from;
    this->from = new char[strlen(from) + 1];
    strcpy(this->from, from);
}
void Repair::setTo(const char* to)
{
    delete[] this->to;
    this->to = new char[strlen(to) + 1];
    strcpy(this->to, to);
}
void Repair::setNote(const char* note)
{
    delete[] this->note;
    this->note = new char[strlen(note) + 1];
    strcpy(this->note, note);
}

//Other functions
void Repair::print()
{
    std::cout << "Room " << id << " from " << from << " to " << to << " for " << note << std::endl;
}
void Repair::free()
{
    if (from != nullptr)
        delete[] from;
    if (to != nullptr)
        delete[] to;
    if (note != nullptr)
        delete[] note;
    id = -1;
}
void Repair::copy(const Repair& other)
{
    this->id = other.id;

    this->from = new char[strlen(other.from) + 1];
    strcpy(this->from, other.from);
    this->to = new char[strlen(other.to) + 1];
    strcpy(this->to, other.to);
    this->note = new char[strlen(other.note) + 1];
    strcpy(this->note, other.note);
}
