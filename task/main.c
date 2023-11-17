
#include "parser/parser.h"
#include "placement/placement.h"
#include "exporter/exporter.h"



int main()
{
	read_input_file();
	placement();
	out_put();
	free_memory();
	
	return 0;

}