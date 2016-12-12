#include <utility>
#include <map>
#include <list>
#include "cells.h"

std::map<std::pair<int, int>, bool> living_cells;
std::list<std::pair<std::pair<int, int>, bool>> revoked;

void summon(coord pos) {
	living_cells[pos] = true;
}

bool alive(coord pos) {
	//Alive when in living_cells, otherwise not
	if (living_cells.find(pos) != living_cells.end())
		return true;
	return false;
}

void update(coord pos) {
	//apply rules
	//First count the neighbouring cells that are alive
	int x = pos.first, y = pos.second, count = 0;
	if (alive(coord(x - 1, y - 1))) count++;
	if (alive(coord(x - 1, y))) count++;
	if (alive(coord(x - 1, y + 1))) count++;
	if (alive(coord(x, y + 1))) count++;
	if (alive(coord(x + 1, y + 1))) count++;
	if (alive(coord(x + 1, y))) count++;
	if (alive(coord(x + 1, y - 1))) count++;
	if (alive(coord(x, y - 1))) count++;

	//Rule 1: Revive dead cells as soon as they have exactly three living neighbours
	//ONLY USE UPDATE FUNCTION ON DEAD CELLS, WHEN ALL LIVING CELLS HAVE ALREADY BEEN UPDATED
	if (!alive(pos) && count == 3) revoked.push_back(cell(pos, true));
	else if (!alive(pos)) return;
	//Rule 2: Kill when less than two livin' neighbours
	else if (count < 2) living_cells[pos] = false;
	//Rule 4: Kill when more than three living neighbours
	else if (count > 3) living_cells[pos] = false;
	//Rule 3: (obvious and redundant) Stay alive when two or three neighbours
	else living_cells[pos] = true;

}

void update_all(void) {
	for (cell c : living_cells) {
		update(c.first);
	}
	next();
}

void next(void) {
	//Summons dead cells according to rule 1: (Add them to the revoked list)
	for (cell c : living_cells) {
		int x = c.first.first, y = c.first.second;
		if (!alive(coord(x - 1, y - 1))) update(coord(x - 1, y - 1));
		if (!alive(coord(x - 1, y))) update(coord(x - 1, y));
		if (!alive(coord(x - 1, y + 1))) update(coord(x - 1, y + 1));
		if (!alive(coord(x, y + 1))) update(coord(x, y + 1));
		if (!alive(coord(x + 1, y + 1))) update(coord(x + 1, y + 1));
		if (!alive(coord(x + 1, y))) update(coord(x + 1, y));
		if (!alive(coord(x + 1, y - 1))) update(coord(x + 1, y - 1));
		if (!alive(coord(x, y - 1))) update(coord(x, y - 1));
	}

	//Add the revived cells to living_cells
	while(revoked.size() > 0) {
		living_cells[revoked.front().first] = revoked.front().second;
		revoked.pop_front();
	}

	//Kill all cells marked as to be killed
	for (std::map<std::pair<int, int>, bool>::iterator it = living_cells.begin(); it != living_cells.end();) {
		if (!(it->second))
			living_cells.erase(it++->first);
		else it++;
	}
}
