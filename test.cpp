#include "abstract_compress.hpp"
#include <glog/logging.h>
#include <iostream>

using namespace std;
using namespace compress;

int main(int argc, char* argv[])
{
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;
    LOG(INFO) << "Hello,GLOG!";
    uint32_t inputLen = 1000;
    uint8_t* input = new uint8_t[inputLen];

    AbstractCompress::getSparseData(input, inputLen);
    AbstractCompress::out2BinFile((char*)input, inputLen, "origin.data");
    delete [] input;
    return 0;
}