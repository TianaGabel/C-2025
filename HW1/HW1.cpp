#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 1) {
        std::cerr << "Error: no arguments should be provided" << std::endl;
        return -1;
    }

    std::cout << "Hello World!" << std::endl;
    return 0;
}


#!/bin/bash
#SBATCH --job-name=parallel_example     # Name of the job
#SBATCH --output=output_%j.txt          # Output file for job (will include job ID)
#SBATCH --error=error_%j.txt            # Error file for job (will include job ID)
#SBATCH --ntasks=1                      # Use 1 task (we will use cores via parallel)
#SBATCH --cpus-per-task=4               # Allocate 4 CPUs (cores) for this job
#SBATCH --time=00:10:00                 # Set maximum runtime (HH:MM:SS)
#SBATCH --mem=4GB                       # Set memory allocation

# Load the necessary module for parallel (if needed)
module load parallel

# Simple task to be executed in parallel
echo "Starting parallel tasks..."

# Run parallel on 4 cores using the `parallel` command
# This will explicitly assign each task to a CPU core and print which core it runs on
seq 0 3 | parallel -j 4 'echo "Running on core $(taskset -c {} echo "number {}") for task number {}"'

echo "Parallel tasks completed."