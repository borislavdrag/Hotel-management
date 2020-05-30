#include "Hotel.h"
using namespace std;

int main()
{
	Hotel t;

	t.getRoom(105).setBeds(3);
	t.getRoom(106).setBeds(3);

	t.checkin(201, "2000-01-01", "2000-01-06", -1);
	t.checkin(106, "2000-03-01", "2000-04-08", -1);
	t.repair(106, "2000-02-29", "2000-03-01", "For the couple");

	t.report("2000-01-01", "2001-01-01");
	t.available("2000-01-01", "2001-01-01", 1);

	fstream out;
	out.open("hotel.data", fstream::out | fstream::trunc);
	t.save(out);
	out.close();

	//t.print();
}