#!/bin/bash
# a sample job submission script to submit an MPI job to the sandyb partition on Midway1

# set the job name to optionpricing
#SBATCH --job-name=optionpricing

# send output to optionpricing.out
#SBATCH --output=optionpricing.out

# receive an email when job starts, ends, and fails
#SBATCH --mail-type=BEGIN,END,DAIL

#SBATCH --account=osmlab

# this job requests 1 core. Cores can be selected from various nodes.
#SBATCH --ntasks=1

# there are many partitions on Midway1 and it is important to specify which
# partition you want to run your job on. Not having the following option, the
# sandby partition on Midway1 will be selected as the default partition
#SBATCH --partition=sandyb

# Run the process 
./BS.exec
