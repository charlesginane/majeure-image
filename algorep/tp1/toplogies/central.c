#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
    int rank, size, len;
    size_t nb_iterations = 15;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];
    MPI_Request request;

    int init = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_library_version(version, &len);
    if (rank == 0) {
        int res = -1;
        MPI_Recv(&res, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (res != -1) {
            printf("Rank Master: receiving data: %d\n", res);
            MPI_Send(&res, 1, MPI_INT, res, 0, MPI_COMM_WORLD);
        }
    }
    else {
        int p = 2;
        MPI_Send(&p, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        int n = 0;
        MPI_Irecv(&n, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &request);
        printf("Rank %d: receives data: %d\n", rank, n);
    }
    MPI_Finalize();
    return 0;
}
