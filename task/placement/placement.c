#include "../database/database.h"
#include "./placement.h"
#include <string.h>

int** grid;
int shortest_length = 9999;

int ***is_link;


void record_is_link()
{
	//init
	is_link = (int***)malloc(num_nets * sizeof(int**));
	for (int i = 0; i < num_nets; i++)
	{
		is_link[i] = (int**)malloc(num_instances * sizeof(int*));
		for (int j = 0; j < num_instances; j++)
		{
			is_link[i][j] = (int*)malloc(num_instances * sizeof(int));
		}
	}
	for (int i = 0; i < num_nets; i++)
	{
		for (int j = 0; j < num_instances; j++)
		{
			for (int n = 0; n < num_instances; n++)
			{
				is_link[i][j][n] = 0;
			}
		}
	}

	//record
	char name1[5];
	char name2[5];
	int n = 0, m = 0;
	for (int i = 0; i < num_nets; i++)
	{
		for (int j = 0; j < nets[i].num_pin-1; j++)
		{
			strcpy(name1, nets[i].pins[j]->name);
			strcpy(name2, nets[i].pins[j+1]->name);
			for (int k = 0; k < num_instances; k++)
			{
				if (strcmp(name1, instances[k].name) == 0)
				{
					n = k;
					break;
				}
			}
			for (int k = 0; k < num_instances; k++)
			{
				if (strcmp(name2, instances[k].name) == 0)
				{
					m = k;
					break;
				}
			}
			is_link[i][n][m] = 1;
			is_link[i][m][n] = 1;
		}
	}
}

int pin_pin_distance(int x,int j)
{
	return ((instances[x].x - instances[j].x) * (instances[x].x - instances[j].x) + (instances[x].y - instances[j].y) * (instances[x].y - instances[j].y));
}

int calculate_add_length(int x)
{
	int total_length = 0;
	for (int i = 0; i < num_nets; i++)
	{
		for (int j = 0; j < num_instances; j++)
		{
			if ((is_link[i][x][j] == 1) && (instances[j].visited == 1))
			{
				total_length += pin_pin_distance(x,j);
			}
		}
	}
	return total_length;
}

void enumerate(int x,int current_length)
{
	if (current_length >= shortest_length)
	{
		return;
	}

	if (x == num_instances)
	{
		if (current_length<shortest_length)
		{
			memcpy(optimal_solution, instances, num_instances * sizeof(struct instance));
			shortest_length = current_length;
		}
		return;
	}

	for (int i = 0; i < die_size; i++)
	{
		for(int j=0;j<die_size;j++)
			if (grid[i][j] == -1)
			{
				grid[i][j] = x;
				instances[x].x = i;
				instances[x].y = j;
				instances[x].visited = 1;
				int add_length=calculate_add_length(x);
				enumerate(x + 1, current_length+add_length);
				grid[i][j] = -1;
				instances[x].visited = 0;
			}
	}
}

void placement()
{
	//init grid
	grid = (int**)malloc(die_size * sizeof(int*));
	for (int i = 0; i < die_size; i++)
	{
		grid[i] = (int*)malloc(die_size * sizeof(int));
    }
	for (int i = 0; i < die_size; i++)
	{
		for (int j = 0; j < die_size; j++)
			grid[i][j] = -1;
	}
	for (int i = 0; i < num_instances; i++)
	{
		instances[i].visited = 0;
	}


	record_is_link();
	//test2();
	optimal_solution = (struct instance*)malloc(num_instances * sizeof(struct instance));
	enumerate(0, 0);

}
//void test2()
//{
//	for (int i = 0; i < num_nets; i++) {
//		for (int j = 0; j <num_instances; j++) {
//			for (int k = 0; k < num_instances; k++) {
//				printf("%d ", is_link[i][j][k]);
//			}
//			printf("\n");
//		}
//		printf("\n");
//	}
//}
void free_memory()
{
	for (int i = 0; i < num_nets; i++)
	{
		for (int j = 0; j < num_instances; j++)
		{
			free(is_link[i][j]);
		}
		free(is_link[i]);
	}
	free(is_link);


	free(instances);
	free(optimal_solution);
	for (int i = 0; i < num_nets; i++)
	{
		free(nets[i].pins);
	}
	free(nets);
	for (int i = 0; i < die_size; i++)
	{
		free(grid[i]);
	}
	free(grid);
	
}