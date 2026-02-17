/* 
 * Header-only helpers for MPI
 * 
 * Copyright (c) 2026 Fernando Muñoz
 * MIT license. See bottom of file.
 */

#ifndef HLIBS_MPI_HELPERS_H
#define HLIBS_MPI_HELPERS_H
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

#endif

/* MIT License.
 *
 * Copyright (c) 2026 Fernando Muñoz.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
