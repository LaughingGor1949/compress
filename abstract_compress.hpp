#ifndef __ABSTRACT_COMPRESS_HPP__
#define __ABSTRACT_COMPRESS_HPP__

#include <stdint.h>
#include <string>

namespace compress{

enum compressStatus
{
    STATUS_SUCCESS = 0,             /* succ */
    STATUS_NOT_INITIALIZED,         /* not initialize */
    STATUS_ALLOC_FAILED,            /* malloc failed */
    STATUS_BAD_PARAM,               /* check para failed */
    STATUS_INTERNAL_ERROR,          /* internal error */
    STATUS_RUNTIME_ERROR,           /* runtime error */
    STATUS_NOT_SUPPORTED,           /* not supported */
    STATUS_RESERVED                 /* reserved */
};
using cpsStatus = compressStatus;


enum
{
    CHAR_BIT = 8,
    CHAR_SIZE = 256,
    UINT8_VALUE_MAX = 255,
    SPARSE_RATE_MAX = 100,
    SPARSE_RATE_MIN = 0
};


inline uint32_t getCeil(uint32_t numerator, uint32_t denominator)
{
    return (numerator + denominator - 1) / denominator;
}

class AbstractCompress
{
public:
    static cpsStatus getSparseData(uint8_t* inputData, uint32_t inputLen, uint8_t sparseRate = 80);
    static cpsStatus out2BinFile(const char* inputData, uint32_t inputLen, std::string fileName);
};

};/* end namespace compress */

#endif/* end if */
