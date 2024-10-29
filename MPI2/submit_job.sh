#!/bin/bash
#SBATCH --job-name=MPI_test2
#SBATCH --output=ex4.txt
#SBATCH --mem=1024
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=4
#SBATCH --time=00:05:00

mpirun -np 4 ./ex4