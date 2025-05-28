#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(hostname, &len);

    printf("Rank %d of %d running on %s\n", rank, size, hostname);
    fflush(stdout);

    if (rank == 0) {
        FILE* fp = fopen("/home/your_username/mpi_outpus/temp_stat.txt", "a");
        if (fp == NULL) {
            perror("Unable to open stats file");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        fprintf(fp, "Job run by %d processes:\n", size);
        for (int i = 0; i < size; i++) {
            fprintf(fp, "Process %d on %s\n", i, hostname); 
        }
        fclose(fp);
    }

    MPI_Finalize();
    return 0;
}
