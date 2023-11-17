#ifndef PARSER_H
#define PARSER_H

#include "../database/database.h"

extern int num_instances;
extern int num_nets;
extern int die_size;
extern struct instance* instances;
extern struct net* nets;

void read_input_file();

void test();

#endif