#!/bin/bash
#SBATCH --job-name=Monte_carlo_test
#SBATCH --output=Monte_carlo3.txt
#SBATCH --mem=1024
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --time=00:05:00

./MC_3