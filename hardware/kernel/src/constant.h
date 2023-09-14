//
// Created by 冯昊 on 2023/8/30.
//

#ifndef TITAN_HARDWARE_CONSTANT_H
#define TITAN_HARDWARE_CONSTANT_H

#include <endian.h>

#include <cstdint>
#include <cstdio>

#ifndef MAX_KEY_LENGTH
#define MAX_KEY_LENGTH 64
#endif

#ifndef MAX_VALUE_LENGTH
#define MAX_VALUE_LENGTH 8192
#endif

#ifndef MAX_INPUT_LENGTH
#define MAX_INPUT_LENGTH 4
#endif

#ifndef MAX_DATA_SIZE
 #define MAX_DATA_SIZE (136 * 1024 * 1024)
//#define MAX_DATA_SIZE (32 * 1024)
#endif

#ifndef MAX_INPUT_BITMAP_SIZE
#define MAX_INPUT_BITMAP_SIZE (136 * 1024 / 8)
#endif

#ifndef PLATFORM_IS_LITTLE_ENDIAN
#define PLATFORM_IS_LITTLE_ENDIAN (__BYTE_ORDER == __LITTLE_ENDIAN)
#endif

namespace xf {
namespace gc {

//constexpr bool kLittleEndian = PLATFORM_IS_LITTLE_ENDIAN;

const uint64_t kBlobMaxHeaderSize = 12;
const uint64_t kBlobMinHeaderSize = 8;
const uint32_t kHeaderMagicNumber = 0x2be0a614ul;
const uint32_t kHeaderVersion1 = 1;
const uint32_t kHeaderVersion2 = 2;
const uint32_t kHasUncompressedDictionary = 1 << 0;

const uint64_t kRecordHeaderSize = 9;

const uint64_t kBlobFooterSize = 32;
const uint64_t kFooterMagicNumber = 0x2be0a6148e39edc6ull;

}  // namespace gc
}  // namespace xf

#endif  // TITAN_HARDWARE_CONSTANT_H
