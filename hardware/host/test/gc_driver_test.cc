//
// Created by 冯昊 on 2023/9/5.
//

#include "gc_driver.h"

#include <cinttypes>

std::string GenKey(uint64_t i) {
  char buf[64];
  snprintf(buf, sizeof(buf), "k-%08" PRIu64, i);
  return buf;
}

std::string GenValue(uint64_t k) {
  if (k % 2 == 0) {
    return std::string(4096 - 1, 'v');
  } else {
    return std::string(4096 + 1, 'v');
  }
}

int main(int argc, char *argv[]) {
  std::string binary(
      "/home/hfeng/code/titan/cmake-build-debug-node27/hardware/kernel/hw_emu/"
      "gc.xclbin");
  uint8_t device_id = 0;
  GCDriver driver(binary, device_id);

  std::vector<std::string> input_blob;
  //  1.blob for key of GenKey [0-1000)
  //  2.blob for key of GenKey [1000-2000)
  //  3.blob for key of GenKey [2000-3000)
//  input_blob.push_back("/home/SmartSSD_Data/hfeng/titan/1.blob");
//  input_blob.push_back("/home/SmartSSD_Data/hfeng/titan/2.blob");
//  input_blob.push_back("/home/SmartSSD_Data/hfeng/titan/3.blob");
    input_blob.push_back("/home/SmartSSD_data/hfeng/titan/11.blob");

  std::string ouput_blob("/home/SmartSSD_data/hfeng/titan/4.blob");
  //  std::string ouput_blob("/home/SmartSSD_Data/hfeng/titan/14.blob");
  std::vector<std::pair<size_t, unsigned char *>> bitmaps;
  std::vector<std::uint64_t> input_entries;
  size_t bitmap_size = 100 / 8 + 1;
  for (int i = 0; i < 1; ++i) {
    auto bitmap = (unsigned char *)aligned_alloc(1024, bitmap_size);
    memset(bitmap, 0, bitmap_size);
    bitmaps.emplace_back(bitmap_size, bitmap);
    input_entries.push_back(2);
  }

  std::vector<std::pair<std::string, uint64_t>> rewrite_keys;

  driver.run_gc_kernel(input_blob, ouput_blob, bitmaps, input_entries, 0,
                       &rewrite_keys);

  //  todo check output_blob and rewrite_keys
  //  assert(rewrite_keys.size() == 3000);
}
