#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    char filename[256];
    snprintf(filename, sizeof(filename), "/tmp/mpi_stat_%s_%d.txt", processor_name, world_rank);
    FILE* fp = fopen(filename, "w");
    if (fp != NULL) {
        fprintf(fp, "Rank %d of %d on processor %s\n", world_rank, world_size, processor_name);
        fclose(fp);
    }

    MPI_Finalize();
    return 0;
}
