#ifndef __LZ77_COMPRESS_HPP__
#define __LZ77_COMPRESS_HPP__

#include "abstract_compress.hpp"

namespace compress
{

class Lz77Compress
{

struct LZ77Window
{
    uint8_t* searchBuff;
    uint8_t* lookaheadBuff;
    uint32_t currentLookaheadBuffLen;
    uint32_t curson;
    uint32_t length;
    uint8_t nextData;
};


public:
Lz77Compress();
cpsStatus lz77Compress(const uint8_t* inputData, uint32_t inputLen, uint8_t* outputData, uint32_t& outputLen);
void findMaxMatch(LZ77Window* window);

protected:
const static uint32_t LZ77_TYPE_BITS = 1;
const static uint32_t LZ77_WINOFF_BITS = 12;
const static uint32_t LZ77_BUFFLEN_BITS = 5;
const static uint32_t LZ77_NEXT_BITS = 8;
const static uint32_t LZ77_WINDOW_SIZE = 4096;
const static uint32_t LZ77_BUFF_SIZE = 32;
const static uint32_t LZ77_PHRASE_BITS = LZ77_TYPE_BITS + LZ77_WINOFF_BITS + LZ77_NEXT_BITS + LZ77_BUFFLEN_BITS;
const static uint32_t LZ77_SYMBOL_BITS = LZ77_TYPE_BITS + LZ77_NEXT_BITS;
};


};

#endif