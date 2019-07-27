#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <omp.h>
#include <iostream>
int main()
{
    int niter = 10000000;
    double x,y;
    //int i = 0;
    int count=0.;
    double z;
    double pi;
    //srand(time(NULL));
    //main loop
    #pragma omp parallel for reduction(+:count)
    for(int ii=0; ii<niter; ii++)
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
    pi = ((double)count/(double)niter)*4.0;          //p = 4(m/n)
    printf("Pi: %f\n", pi);

    return 0;
}



