#include "floorplan.h"

BLOCK::BLOCK(string name, int wid, int hei){

	leftchild = NULL;
	rightchild = NULL;
	parent = NULL;
	this->name = name;
	this->w = wid;
	this->h = hei;
	this->x = 0;
	this->y = 0;

}

TERMINAL::TERMINAL(string name, int x, int y){

	this->x = x;
	this->y = y;

}

GRAPH::GRAPH(){

	root = NULL;
	AllBlock.clear();
	AllTerminal.clear();
	boundry_x = 0;
	boundry_y = 0;
	max_x = 0;
	max_y = 0;
	best_cost = numeric_limits<int>::max();
	start = clock();

}
