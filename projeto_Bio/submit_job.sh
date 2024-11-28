#!/bin/bash
#SBATCH --job-name=BIO
#SBATCH --output=BIO2.txt
#SBATCH --error=BIO.err
#SBATCH --mem=1024
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=4
#SBATCH --time=00:05:00

mpirun -np 4 ./ex2
