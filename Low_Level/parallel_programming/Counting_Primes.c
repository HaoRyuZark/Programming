#include <math.h>
#include <openmpi-x86_64/mpi.h>
#include <stdio.h>

/*
 * To run and compile:
 *
 * 1. module load mpi/openmpi-x86_64 
 * 2. mpicc -lm Count_Primes.c 
 * 3. mpirun ./a.out 
 *
 * */
int _is_prime(int n) {
    
    if (n < 2) {
        return 0;
    }

    int limit = sqrt(n);
    
    for (int i = 2; i <= limit; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    
    return 1;
}

int _count_primes(unsigned int start, unsigned int end) {
    
    int count = 0;

    for (int i = start; i <= end; i++) {

        if (_is_prime(i)) {
            count++;
            printf("Prime found! %d\n", i);
        } 
    }

    return count;
}

void count_primes(unsigned int start, unsigned int end) {
    
    int size; 
    int rank; 

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int len = end - start + 1;
    int base = len / size;
    int remainder = len % size;

    int local_n = base + (rank < remainder ? 1 : 0);

    int start_ = start + rank * base + (rank < remainder ? rank : remainder);
    int end_   = start_ + local_n - 1;

    int loc_count = _count_primes(start_, end_);
    
    if (rank == 0) {
        
        int x;   
        for (int i = 1; i < size; i++) {
            MPI_Recv(&x, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            loc_count += x;
        }

        printf("Total number of primes: %d\n", loc_count);

    } else {
        
        MPI_Send(&loc_count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } 
}

int main(int argc, char** argv) {
    
    MPI_Init(&argc, &argv);
    count_primes(2, 10000);
    MPI_Finalize();

    return 0;
}
