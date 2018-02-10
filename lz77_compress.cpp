#include "lz77_compress.hpp"
#include <glog/logging.h>

namespace compress{

Lz77Compress::Lz77Compress()
{

}

cpsStatus Lz77Compress::lz77Compress(const uint8_t* inputData, uint32_t inputLen, uint8_t* outputData, uint32_t& outputLen)
{
    if (inputData == NULL || outputData == NULL)
    {
        LOG(WARNING) << "input/output point is NULL!";
        return STATUS_BAD_PARAM;
    }
    uint8_t searchBuff[LZ77_WINDOW_SIZE] = {0};
    uint8_t lookaheadBuff[LZ77_BUFF_SIZE] = {0};
    LZ77Window window = {searchBuff, lookaheadBuff, 0, 0, 0, 0};

    uint32_t inputOffset = 0;
    uint32_t outputOffset = 0;
    uint32_t outputDataLenMax = outputLen;
    if (inputOffset < inputLen)
    {
        uint32_t searchBuffInInput = (inputOffset > LZ77_WINDOW_SIZE)? inputOffset - LZ77_WINDOW_SIZE: 0;
        memcpy(window.searchBuff + LZ77_WINDOW_SIZE - inputOffset + searchBuffInInput,
               inputData + searchBuffInInput,
               inputOffset - searchBuffInInput);
        window.currentLookaheadBuffLen = (outputOffset + LZ77_BUFF_SIZE > outputDataLenMax)?
            (outputDataLenMax - outputOffset): LZ77_BUFF_SIZE;
        memcpy(window.lookaheadBuff, inputData + inputOffset, window.currentLookaheadBuffLen);
        findMaxMatch(&window);

    }
    
}


void Lz77Compress::findMaxMatch(LZ77Window* window)
{
    window->length = 0;
    for (uint32_t i = 0; i < LZ77_WINDOW_SIZE - window->length; ++i)
    {
        uint32_t j = 0;
        for (j = 0; j < window->currentLookaheadBuffLen; ++j)
        {
            if (window->searchBuff[i + j] != window->lookaheadBuff[j])
            {
                break;
            }
        }
        if (j > window->length)
        {
            window->length = j;
            window->curson = i;
        }
    }
}

}