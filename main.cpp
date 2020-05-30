#include "Hotel.h"
using namespace std;

int main()
{
	Hotel t;

	t.checkin(201, "2000-01-01", "2000-01-06", -1);
	t.checkin(106, "2000-03-01", "2000-04-08", -1);

	//t.report("2000-01-01", "2001-01-01");
	t.available("2000-01-01", "2001-01-01", 1);

	//t.print();
}