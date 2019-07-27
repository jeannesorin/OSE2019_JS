#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
    int niter = 10000000;
    double x,y;
    int i;
    int count=0;
    double z;
    double pi;
    int rank, size, sum, my_rank, Trank, loop;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    my_rank = 1;
    MPI_Reduce(&my_rank, &Trank, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
     if (rank==0){
        loop = round(niter/Trank);          //p = 4(m/n)
        printf("Loop size: %f\n", loop);
    }
    MPI_Bcast(&loop, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("I am rank %i and the value is %i\n", rank, loop);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //srand(time(NULL));
    //main loop
    for (i=0; i<loop; ++i)
    {
        //get random points
        x = (double)random()/RAND_MAX;
        y = (double)random()/RAND_MAX;
        z = sqrt((x*x)+(y*y));
        //check to see if point is in unit circle
        if (z<=1)
        {
            ++count;
        }
    }
    MPI_Reduce(&count, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank==0){

        pi = (double)sum/((double)loop*(double)Trank)*4.0;          //p = 4(m/n)
        printf("Pi: %f\n", pi);

    }
    MPI_Finalize();
    return 0;
}
