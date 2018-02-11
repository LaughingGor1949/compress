#include "lz77_compress.hpp"
#include <glog/logging.h>

namespace compress{

Lz77Compress::Lz77Compress()
{

}

cpsStatus Lz77Compress::compress(const uint8_t* input, uint32_t inputLen, uint8_t* output, uint32_t& outputLen)
{
    if (input == nullptr || output == nullptr)
    {
        LOG(WARNING) << "input/output point is NULL!";
        return STATUS_BAD_PARAM;
    }
    LZ77Window window = {nullptr, 0, nullptr, 0, 0, 0, 0};
    uint32_t inputOffset = 0;
    uint32_t outputOffset = 0;
    const uint32_t OUTPUT_LEN_MAX = outputLen;
    while (inputOffset < inputLen)
    {
        window.searchSize = (inputOffset > SEARTCH_BUFF_SIZE)? (inputOffset - SEARTCH_BUFF_SIZE): SEARTCH_BUFF_SIZE;
        window.search = input + inputOffset - window.searchSize;
        window.lookahead = input + inputOffset;
        window.lookaheadSize = (inputLen - inputOffset > LOOKAHEAD_BUFF_SIZE)? LOOKAHEAD_BUFF_SIZE: inputLen - inputOffset;
        //findMaxMatch
        if (outputOffset + CODE_BYTES <= OUTPUT_LEN_MAX)
        {
            outputOffset += CODE_BYTES;
            inputOffset += window.length + 1;
            //encode()
        }
        else
        {
            LOG(WARNING) << "output buff is not enough!";
            break;
        }
    }
}


void Lz77Compress::findMaxMatch(LZ77Window* window)
{
    window->length = 0;
    for (uint32_t searchIndex = 0; searchIndex < window->searchSize; ++searchIndex)
    {
        uint32_t lookaheadIndex = 0;
        for (lookaheadIndex = 0; lookaheadIndex < window->lookaheadSize; ++lookaheadIndex)
        {
            if (window->search[searchIndex + lookaheadIndex] != window->lookahead[lookaheadIndex])
            {
                break;
            }
        }
        if (lookaheadIndex > window->length)
        {
            window->length = lookaheadIndex;
            window->pos = window->searchSize - searchIndex;
        }
    }
}

}/* end namespace */