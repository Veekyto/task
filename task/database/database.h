#ifndef DATABASE_H
#define DATABASE_H


#include <stdio.h>
#include <stdlib.h>

extern int num_instances;
extern int num_nets;
extern int die_size;

struct instance
{
	char name[5];
	int x;
	int y;
	int visited;
};

struct net
{
	char name[5];
	int num_pin;
	struct instance** pins;
};

extern struct instance* instances;
extern struct net* nets;
extern struct instance* optimal_solution;
extern int** grid;

#endif
