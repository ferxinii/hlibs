/* 
 * Header-only Union-Find implementation.
 * 
 * Copyright (c) 2026 Fernando Muñoz
 * MIT license. See bottom of file.
 */

#ifndef LIB_UNION_FIND_H
#define LIB_UNION_FIND_H


/* INTERFACE */
static inline void UF_initialize(int N, int UF_parent[N], int UF_rank[N]);
static inline int UF_find(int x, int *parent);
static inline void UF_union(int x, int y, int *parent, int *rank);
static inline int UF_count_sets_and_label(int N, int UF_parent[N], int OUT_labels[N]);



/* IMPLEMENTATION */
#include <string.h>

static inline void UF_initialize(int N, int UF_parent[N], int UF_rank[N])
{
    memset(UF_rank, 0, sizeof(int) * N);
    for (int ii=0; ii<N; ii++) 
        UF_parent[ii] = ii;  /* Each sphere is its own cluster */
}


static inline int UF_find(int x, int *parent)
{   /* Find root element of the set where x belongs to, i.e., unique representative of such set */
    if (parent[x] != x) {
        /* Path compression makes the tree as flat as possible */
        /* by pointing directly to the root */
        parent[x] = UF_find(parent[x], parent); 
    }
    return parent[x];
}


static inline void UF_union(int x, int y, int *parent, int *rank)
{   /* Union operation with rank */
    int rootX = UF_find(x, parent);
    int rootY = UF_find(y, parent);

    if (rootX == rootY) return;

    if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
    else if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
    else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}


static inline int UF_count_sets_and_label(int N, int UF_parent[N], int OUT_labels[N])
{
    for (int ii=0; ii<N; ii++) OUT_labels[ii] = -1;

    int cluster_count = 0;
    for (int ii = 0; ii<N; ii++) {
        int root = UF_find(ii, UF_parent);
        if (OUT_labels[root] == -1) 
            OUT_labels[root] = cluster_count++;  /* Assign new cluster ID */
        OUT_labels[ii] = OUT_labels[root];       /* Ensure every element gets correct label */
    }

    return cluster_count;
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

