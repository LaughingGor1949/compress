#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <glog/logging.h>
#include "abstract_compress.hpp"

using namespace std;

namespace compress{
cpsStatus AbstractCompress::getSparseData(uint8_t* inputData, uint32_t inputLen, uint8_t sparseRate)
{
    if (inputData == NULL)
    {
        LOG(WARNING) << "input point is NULL!";
        return STATUS_BAD_PARAM;
    }
    if ((sparseRate == SPARSE_RATE_MIN) || (sparseRate >= SPARSE_RATE_MAX))
    {
        LOG(WARNING) << "sparse rate = " << sparseRate << " should be in (0, 100)!";
        return STATUS_BAD_PARAM;
    }
    srand(static_cast<int>(time(NULL)));
    uint32_t randDataMax = getCeil(UINT8_VALUE_MAX * SPARSE_RATE_MAX, SPARSE_RATE_MAX - sparseRate);
    uint32_t randData = 0;
    for (uint32_t i = 0; i < inputLen; ++i)
    {
        randData = rand() %  (randDataMax + 1);
        if (randData >= UINT8_VALUE_MAX)
        {
            inputData[i] = 0;
        }
        else
        {
            inputData[i] = static_cast<uint8_t>(randData);
        }
    }
    LOG(INFO) << "data size is " << inputLen << " bytes";
    LOG(INFO) << "data sparse is " << static_cast<int>(sparseRate) << "%";
    return STATUS_SUCCESS;
}


cpsStatus AbstractCompress::out2BinFile(const char* inputData, uint32_t inputLen, string fileName)
{
    if (inputData == NULL)
    {
        LOG(WARNING) << "input point is NULL!";
        return STATUS_BAD_PARAM;
    }

    ofstream ofile(fileName, ios::binary);
    if (!ofile)
    {
        LOG(WARNING) << "open " << fileName << " fail!";
        return STATUS_RUNTIME_ERROR;
    }
    ofile.write(inputData, inputLen);
    ofile.close();
    return STATUS_SUCCESS;
}

}
