/* 
 * Header-only file management helpers.
 * 
 * Copyright (c) 2026 Fernando Muñoz
 * MIT license. See bottom of file.
 */


#ifndef HLIBS_FILES_H
#define HLIBS_FILES_H

#include <stdio.h>

static inline int count_lines(FILE *file)
{
    const int BUF_SIZE = 2048;
    char buf[BUF_SIZE];
    int counter = 0;
    while(1) {
        int nread = fread(buf, 1, BUF_SIZE, file);
        if (ferror(file)) return -1;

        for(int ii=0; ii<nread; ii++) if (buf[ii] == '\n') counter++;

        if (nread < BUF_SIZE && feof(file)) {
            if (nread > 0 && buf[nread - 1] != '\n') counter++;
            break; 
        }
    }
    rewind(file);
    return counter;
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

