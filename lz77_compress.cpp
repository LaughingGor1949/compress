#include "lz77_compress.hpp"

namespace compress{

Lz77Compress::Lz77Compress()
{

}

cpsStatus Lz77Compress::lz77Compress(const uint8_t* inputData, uint32_t inputLen, uint8_t* outputData, uint32_t& outputLen)
{
    uint8_t windowData[LZ77_WINDOW_SIZE] = {0};
    uint8_t buffData[LZ77_BUFF_SIZE] = {0};
}

}