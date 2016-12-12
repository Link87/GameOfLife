#pragma once

#ifndef CELLS_HEADER
#define CELLS_HEADER

//The x and y coordinates
typedef std::pair<int, int> coord;

//First: coordinates of the cell, Second: Whether the cell is still alive the next day
typedef std::pair<std::pair<int, int>, bool> cell;

//Set of all cells that are alive
extern std::map<std::pair<int, int>, bool> living_cells;

//A set of all cells to be revoked the next day
extern std::list<std::pair<std::pair<int, int>, bool>> revoked;

//creates a new cell at position pos
void summon(coord pos);

//checks whether cell at position pos is alive
bool alive(coord pos);

//Applies the 2nd to 4th rule to the cell at position pos when it is alive
//or otherwise the first rule
void update(coord pos);

//Updates all cells and calls next()
void update_all(void);

//The next day is comin':
//Cells to be reborn are now reborn,
//Cells to die now come to death
void next(void);

#endif CELLS_HEADER
