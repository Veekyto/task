
#include "parser.h"
#include "../database/database.h"
#include <string.h>


int num_instances;
int num_nets;
int die_size;
struct instance* instances;
struct net* nets;


void read_input_file()
{
	FILE* input_file=fopen("../benchmarks/case0.txt","r");
	if (input_file == NULL)
	{
		printf("open file error");
		return;
	}
	fscanf(input_file, "DieSize %d %d\n", &die_size, &die_size);
	fscanf(input_file, "NumInstances %d\n", &num_instances);
	instances = (struct instance*)malloc(num_instances * sizeof(struct instance));
	for (int i = 0; i < num_instances; i++)
	{
		fscanf(input_file, "Inst %s\n", instances[i].name);
	}

	fscanf(input_file, "NumNets %d\n", &num_nets);
	nets = (struct net*)malloc(num_nets * sizeof(struct net));

	for (int j = 0; j < num_nets; j++)
	{
		fscanf(input_file, "Net %s %d\n", nets[j].name, &nets[j].num_pin);
		nets[j].pins = (struct instance**)malloc(nets[j].num_pin * sizeof(struct instance*));
		for (int k = 0; k < nets[j].num_pin; k++)
		{
			char instance_name[5];
			fscanf(input_file, "Pin %s\n", instance_name);
			for (int n = 0; n < num_instances; n++)
			{
				if (strcmp(instance_name, instances[n].name) == 0)
				{
					nets[j].pins[k] = &instances[n];
					break;
				}
			}
		}

		
	}
	
	fclose(input_file);

}
//
//void free_memory()
//{
//	
//	for (int i = 0; i < num_nets; i++)
//	{
//		free(nets[i].pins);
//	}
//	free(nets);
//}

void test()
{
	printf("%d\n", die_size);
	printf("%d\n", num_instances);

	for (int i = 0; i < num_instances; i++)
	{
		printf("%s ", instances[i].name);
	}
	printf("%d\n", num_nets);
	for (int i = 0; i < num_nets; i++)
	{
		printf("Net %s %d\n", nets[i].name, nets[i].num_pin);
		for (int j = 0; j < nets[i].num_pin; j++)
			printf("Pin %s\n", nets[i].pins[j]->name);
	}
}