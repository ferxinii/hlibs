/* 
 * Header-only simple statistics library
 * Computes first and second moments of a sample robustly in an incremental manner,
 * internally using welford's online algorithm. Can be extended for 3rd and 4rth moments.
 * 
 * Copyright (c) 2026 Fernando Muñoz
 * MIT license. See bottom of file.
 */

#ifndef HLIBS_STATS_H
#define HLIBS_STATS_H
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct sample {  
    int N;
    double mu;           /* Running mean */
    double M2;           /* Sum of squared deviations */
} s_sample;


typedef enum {
    STATS_POPULATION,
    STATS_SAMPLE,
} e_stats_type;


static inline s_sample stats_init_sample()
{
    return (s_sample){0};
}

static inline s_sample stats_add_sample(s_sample sample, double x)
{
    double d = x - sample.mu;
    int N = sample.N + 1;
    double mu = sample.mu + d/N;
    double M2 = sample.M2 + (x - mu) * (x - sample.mu);
    return (s_sample){ .N = N, .mu = mu, .M2 = M2 };
}


static inline s_sample stats_merge_samples(s_sample A, s_sample B)
{
    if (A.N == 0) return B;
    if (B.N == 0) return A;

    double d = B.mu - A.mu;
    int N_AB = A.N + B.N;
    double mu_AB = (A.N*A.mu + B.N*B.mu) / N_AB;
    double M2_AB = A.M2 + B.M2 + d*d*A.N*B.N/N_AB;
    return (s_sample){ .N = N_AB, .mu = mu_AB, .M2 = M2_AB };
}


static inline double stats_mean(s_sample sample)
{
    return sample.mu;
}

static inline double stats_variance(s_sample sample, e_stats_type type)
{
    switch (type) {
        case STATS_POPULATION: 
            return sample.N == 0 ? 0 : sample.M2 / sample.N;

        case STATS_SAMPLE:
            return sample.N <= 1 ? 0 : sample.M2 / (sample.N - 1);
    }
}

static inline double stats_standard_deviation(s_sample sample, e_stats_type type)
{
    return sqrt(stats_variance(sample, type));
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
