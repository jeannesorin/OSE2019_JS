#!/bin/bash
# a sample job submission script to submit an MPI job to the broadwl partition on Midway
# please change the --partition option if you want to use another partition on Midway

# set the job name to pi_hybrid-mpi
#SBATCH --job-name=pi_hybrid-mpi

# send output to pi_hybrid.out
#SBATCH --output=pi_hybrid.out

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

# Set OMP_NUM_THREADS to the number of cpus per tasj we asked for
export OMP_NUM_THREATS=4


# Run the process with mpirun. Notice -n is not required. mpirun will
# automatically figure out how many processes to run from the slurm options
mpirun ./pi_hybrid.exec


