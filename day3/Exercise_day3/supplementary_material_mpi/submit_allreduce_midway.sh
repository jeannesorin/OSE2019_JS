#!/bin/bash
# a sample job submission script to submit an MPI job to the broadwl partition on Midway
# please change the --partition option if you want to use another partition on Midway

# set the job name to allreduce-mpi
#SBATCH --job-name=allreduce-mpi

# send output to hello-mpi.out
#SBATCH --output=allreduce.out

# receive an email when job starts, ends, and fails
#SBATCH --mail-type=BEGIN,END,DAIL

# this job requests 4 cores. Cores can be selected from various nodes.
#SBATCH --ntasks=4

# there are many partitions on Midway1 and it is important to specify which
# partition you want to run your job on. Not having the following option, the
# sandby partition on Midway1 will be selected as the default partition
#SBATCH --partition=broadwl

# load the openmpi module
module load openmpi

# Run the process with mpirun. Notice -n is not required. mpirun will
# automatically figure out how many processes to run from the slurm options
mpirun ./allreduce.exec

