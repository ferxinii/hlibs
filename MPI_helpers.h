
#include <MPI.h>
#include <stdbool.h>
#include <stdlib.h>


static inline void MPIh_initialize(int argc, char **argv, int *rank_MPI, int *size_MPI) 
{
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, rank_MPI);
    MPI_Comm_size(MPI_COMM_WORLD, size_MPI);
}


static inline int MPIh_schedule_work(int rank_MPI, int size_MPI, int N_tot)
{
    int workload_MPI = N_tot / size_MPI;
    int remainder_MPI = N_tot % size_MPI;
    if (rank_MPI == size_MPI - 1) return workload_MPI + remainder_MPI;
    else return workload_MPI;
}


static inline int MPIh_malloc_parallel(size_t size, void **out)
{
    if (!out || size <= 0) return 0;
    bool local_error = false, global_error = false;

    void *local_out = malloc(size);
    if (!local_out) local_error = true;

    MPI_Allreduce(&local_error, &global_error, 1, MPI_C_BOOL, MPI_LOR, MPI_COMM_WORLD);
    if (global_error) {
        if (local_out) free(local_out); 
        *out = NULL;
        return 0;
    } 
    *out = local_out;
    return 1;
}

