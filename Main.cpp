#include <utility>
#include <map>
#include <list>
#include "cells.h"

int main(void) {

	summon(coord(2, 4));
	summon(coord(3, 4));
	summon(coord(4, 4));

	while (true) {
		update_all();
	}
	return 0;
}