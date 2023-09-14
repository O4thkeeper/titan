//
// Created by 冯昊 on 2023/8/29.
//

#ifndef TITAN_HARDWARE_GC_KERNEL_H
#define TITAN_HARDWARE_GC_KERNEL_H

#include <ap_int.h>
//#include <assert.h>
//#include <iostream>

#include <cstdint>
#include <cstdio>
#include <cstring>

#include "constant.h"
#include "file_format.h"

extern "C" {
void gcKernel(
    const unsigned char (*input_datas)[MAX_DATA_SIZE],  // Input data array
    const unsigned char (
        *input_bitmaps)[MAX_INPUT_BITMAP_SIZE],  // Input bitmap array
    unsigned char* output_data,                  // Output Result
    unsigned char* output_key,                   // Index of output result
    uint64_t* output_meta,  // Meta data of output result: [0]num, [1]size of
                            // data, [2]size of key
    uint64_t* lengths,      // length of every input data
    uint64_t* entries,      // num of entries of every input data
    uint64_t size           // size of input_datas and input_bitmaps
);
}

#endif  // TITAN_HARDWARE_GC_KERNEL_H
