#ifndef __LZ77_COMPRESS_HPP__
#define __LZ77_COMPRESS_HPP__

#include "abstract_compress.hpp"

namespace compress
{


class Lz77Compress
{
private:
    enum
    {
        SEARTCH_BUFF_BITS = 11,
        LOOKAHEAD_BUFF_BITS = 5,
        NEXT_CHAR_BITS = 8,
        SEARTCH_BUFF_SIZE = 2048,
        LOOKAHEAD_BUFF_SIZE = 32,
        CODE_BITS = 24,
        CODE_BYTES = 3
    };
    struct LZ77Window
    {
        const uint8_t* search;
        uint32_t searchSize;
        const uint8_t* lookahead;
        uint32_t lookaheadSize;
        uint32_t pos;
        uint32_t length;
        uint8_t next;
    };
public:
    Lz77Compress();
    cpsStatus compress(const uint8_t* input, uint32_t inputLen, uint8_t* output, uint32_t& outputLen);
    void findMaxMatch(LZ77Window* window);
};/* end class */


};/* end namespace */

#endif