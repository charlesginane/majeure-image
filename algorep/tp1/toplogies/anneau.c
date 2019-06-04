#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
    int rank, size, len;
    size_t nb_iterations = 15;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];
    MPI_Request request;

    int init = 0;
    MPI_Init(&argc, &argv);
    while (1) {
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Get_library_version(version, &len);
        int res = 0;
        if (rank == 0) {
            if (init) {
                MPI_Recv(&res, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Rank %d: Receive %d\n", rank, res);
                break;
            }
            init = 1;
            MPI_Send(&rank, 1, MPI_INT, (rank + 1), 0, MPI_COMM_WORLD);
        }
        else {
            MPI_Recv(&res, 1, MPI_INT,  MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Rank %d: Receive %d\n", rank, res);
            if (rank == size - 1)
                MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            else
                MPI_Send(&rank, 1, MPI_INT, (rank + 1), 0, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}
