#include <iostream>
#include <cmath>
#include <mpi.h>
#include <omp.h>

#define _USE_MATH_DEFINES

const int niter = 500000000;

int main(int argc, char *argv[] ){

    int rank, size, my_rank, Trank, loop;
    int iam = 0, np = 1;
    int i;
    double sum = 0.0, tsum = 0.0;
    double pi = 0.0;
    int count = 0;
    double x,y;
    double w;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    my_rank = 1;

    MPI_Reduce(&my_rank, &Trank, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    //printf("My rank is %i and Trank is %i\n", my_rank, Trank);    

    if (rank==0){
	printf("My rank is %i and Trank is %i\n", my_rank, Trank);
    	printf("Trank is %i\n", Trank);
	//printf("Loop is %i\n", loop);
	loop = round(niter/Trank);
        printf("Loop size: %i\n", loop);
        w = 1.0/(double(loop)*double(Trank));
	printf("w is %e\n", w);
    }	

    MPI_Bcast(&loop, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&w, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    printf("I am using %i OMP threads in cluster (rank) %i and the value is %i\n", rank, omp_get_max_threads(),  loop);

    MPI_Comm_size(MPI_COMM_WORLD, &size);


    //const double w = 1.0/double(loop)*double(Trank);

    double time = -omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i<loop; ++i) {
        double x = (i+0.5)*w;
        sum += 4.0/(1.0+x*x);
    }
    
    MPI_Reduce(&sum, &tsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank==0){
        printf("Have reduced");
   	//pi = (double)tsum/((double)loop);
   
        pi = tsum*w;

        time += omp_get_wtime();

        std::cout << niter
              << " steps approximates pi as : "
              << pi
              << ", with relative error "
              << std::fabs(M_PI-pi)/M_PI
              << std::endl;
        std::cout << "the solution took " << time << " seconds" <<std::endl;
	}
    MPI_Finalize();

    return(0);
}
