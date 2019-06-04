#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
    int rank, size, len;
    size_t nb_iterations = 15;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];

    MPI_Init(&argc, &argv);
    for (size_t i = 0; i < nb_iterations; ++i) {
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Get_library_version(version, &len);
        int res;
        if (rank == 0) {
            if (i != 0) {
                char res[15];
                MPI_Recv(&res, 4, MPI_BYTE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Process %d: Receive pong\n", rank);
            }
            printf("Process %d: Sending ping\n", rank);
            MPI_Send("ping", 4, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
        }
        else {
            char res[15];
            MPI_Recv(&res, 4, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d: Receive ping\n", rank);
            printf("Process %d: Sending pong\n", rank);
            MPI_Send("pong", 4, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}
