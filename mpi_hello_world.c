#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCS 128
#define MAX_NAME 256

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_size, world_rank, name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Get_processor_name(processor_name, &name_len);

    printf("Rank %d on %s\n", world_rank, processor_name);

    // Збираємо імена всіх вузлів
    char all_names[MAX_PROCS][MAX_NAME];
    char my_name[MAX_NAME];
    strncpy(my_name, processor_name, MAX_NAME);

    MPI_Gather(my_name, MAX_NAME, MPI_CHAR, all_names, MAX_NAME, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("\n--- Node usage summary ---\n");
        int counts[MAX_PROCS] = {0};
        char unique[MAX_PROCS][MAX_NAME];
        int unique_count = 0;

        for (int i = 0; i < world_size; i++) {
            int found = 0;
            for (int j = 0; j < unique_count; j++) {
                if (strcmp(all_names[i], unique[j]) == 0) {
                    counts[j]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(unique[unique_count], all_names[i]);
                counts[unique_count]++;
                unique_count++;
            }
        }

        for (int i = 0; i < unique_count; i++) {
            printf("%s: %d processes\n", unique[i], counts[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
