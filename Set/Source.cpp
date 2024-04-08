#include <iostream>

#include "Set.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main() {
	{
		Set set(13);
		set.add(0);
		set.add(5);
		set.add(7);
		set.add(13);

		set.print();

		//set.remove(0);
		//set.remove(7);
		//set.remove(13);
		//set.add(3);
		//set.add(13);

		Set set2(7);
		set2.add(0);
		set2.add(2);
		set2.add(7);
		set2.add(1);
		set2.add(6);
		set2.add(5);

		set2.print();

		Set intersection = setIntersection(set, set2);
		intersection.print();

		Set unionn = setUnion(set, set2);
		unionn.print();
	}
	_CrtDumpMemoryLeaks();
}