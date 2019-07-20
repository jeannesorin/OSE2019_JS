#!/bin/bash -l

#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

#SBATCH --time=00:01:00


#SBATCH --job-name=Pi
#SBATCH --output=Pi.out
#SBATCH --error=Pi.err



### openmp executable
./pi_finite_diff.cpp.exec
