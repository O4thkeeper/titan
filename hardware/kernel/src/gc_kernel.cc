//
// Created by 冯昊 on 2023/8/29.
//

#include "gc_kernel.h"

extern "C" {
void gcKernel(const unsigned char (*input_datas)[MAX_DATA_SIZE],
              const unsigned char (*input_bitmaps)[MAX_INPUT_BITMAP_SIZE],
              unsigned char* output_data, unsigned char* output_key,
              uint64_t* output_meta, uint64_t* lengths, uint64_t* entries,
              uint64_t size) {
#pragma HLS INTERFACE m_axi port = input_datas offset = slave bundle = gmem
#pragma HLS INTERFACE m_axi port = input_bitmaps offset = slave bundle = gmem
#pragma HLS INTERFACE m_axi port = output_data offset = slave bundle = gmem
#pragma HLS INTERFACE m_axi port = output_key offset = slave bundle = gmem
#pragma HLS INTERFACE m_axi port = output_meta offset = slave bundle = gmem
#pragma HLS INTERFACE m_axi port = lengths offset = slave bundle = gmem
#pragma HLS INTERFACE m_axi port = entries offset = slave bundle = gmem
#pragma HLS INTERFACE s_axilite port = input_datas
#pragma HLS INTERFACE s_axilite port = input_bitmaps
#pragma HLS INTERFACE s_axilite port = output_data
#pragma HLS INTERFACE s_axilite port = output_key
#pragma HLS INTERFACE s_axilite port = output_meta
#pragma HLS INTERFACE s_axilite port = lengths
#pragma HLS INTERFACE s_axilite port = entries
#pragma HLS INTERFACE s_axilite port = size
#pragma HLS INTERFACE s_axilite port = return

  uint64_t cur_output_data_offset = 0;
  uint64_t cur_output_key_offset = 0;
  uint64_t* p_cur_output_data_offset = &cur_output_data_offset;
  uint64_t* p_cur_output_key_offset = &cur_output_key_offset;
  uint64_t rewrite_key_num = 0;
  xf::gc::EncodeHeader(output_data, p_cur_output_data_offset);

  for (uint64_t i = 0; i < size; ++i) {
    const unsigned char* input_data = input_datas[i];
    const unsigned char* input_bitmap = input_bitmaps[i];
    unsigned char key[MAX_KEY_LENGTH];
    unsigned char value[MAX_VALUE_LENGTH];
    uint32_t key_length = 0;
    uint32_t value_length = 0;
    uint64_t cur_input_data_offset = 0;
    uint64_t* p_cur_input_data_offset = &cur_input_data_offset;

    xf::gc::DecodeHeader(input_data, p_cur_input_data_offset);

    uint64_t entry_num = entries[i];
    for (uint64_t j = 0; j < entry_num; ++j) {
      xf::gc::SetZero(key, MAX_KEY_LENGTH);
      xf::gc::SetZero(value, MAX_VALUE_LENGTH);

      bool valid = xf::gc::CheckValid(j, input_bitmap);

      xf::gc::GetKV(input_data, p_cur_input_data_offset, valid, key, key_length,
                    value, value_length);

      if (valid) {
        xf::gc::PutOutputKey(output_key, key, key_length,
                             p_cur_output_key_offset,
                             *p_cur_output_data_offset);
        xf::gc::PutOutputData(output_data, key, key_length, value, value_length,
                              p_cur_output_data_offset);
        rewrite_key_num++;
      }
    }

    xf::gc::DecodeFooter(input_data, lengths[i]);
  }
  xf::gc::EncodeFooter(output_data, p_cur_output_data_offset);
  output_meta[0] = rewrite_key_num;
  output_meta[1] = *p_cur_output_data_offset;
  output_meta[2] = *p_cur_output_key_offset;
  //  todo more file meta: size, entries, level, smallest/largest key
}
}