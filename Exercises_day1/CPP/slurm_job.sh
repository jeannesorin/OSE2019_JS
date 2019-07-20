#!/bin/bash -l

#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

#SBATCH --time=00:01:00


#SBATCH --job-name=GiveMyName
#SBATCH --output=GiveMyName.out
#SBATCH --error=GiveMyName.err



### openmp executable
./hidiho.exe
