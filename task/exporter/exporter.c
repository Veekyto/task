
#include "exporter.h"


struct instance* optimal_solution;
void out_put() 
{
    FILE* out_file = fopen("../the_optimal_solution.txt", "w");
    if (out_file == NULL) {
        printf("Error opening file!\n");
        return;
    }

  
    for (int i = 0; i < num_instances; i++) {
        fprintf(out_file, "%s %d %d\n", optimal_solution[i].name, optimal_solution[i].x, optimal_solution[i].y);
    }

    fclose(out_file);
}
