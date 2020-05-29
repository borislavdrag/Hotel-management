#include "Hotel.h"
using namespace std;

int main()
{
	Hotel t;

	t.getRoom(201).setBeds(3);

	Hotel t2 = t;

	t2.print();
}