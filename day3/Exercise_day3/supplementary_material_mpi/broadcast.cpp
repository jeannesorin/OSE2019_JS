#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, data;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int root_process = 0;
    if (rank==0) {
        //printf("enter a value:\n");
        //fflush(stdout);
        //scanf ("%d",&data);
	data = 268.94;
    }

    /* broadcast the value of data of rank 0 to all ranks */
    MPI_Bcast(&data, 1, MPI_INT, root_process, MPI_COMM_WORLD);
    printf("I am rank %i and the value is %i\n", rank, data);
    MPI_Finalize();
    return 0;
}
