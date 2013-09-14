#include "Stream.hpp"
#include <iostream>
#include "util/check.hpp"

Stream::Stream() {}

Stream::~Stream() {
    if(mHandle != nullptr) {
        alureDestroyStream(mHandle, 0, NULL);
    }
}

void Stream::loadFromFile(const std::string& path) {
    alureStreamSizeIsMicroSec(AL_TRUE);
    mHandle = alureCreateStreamFromFile(path.c_str(), 250000, 0, NULL);
}

void Stream::loadFromMemory(const ALubyte *data, ALsizei length) {
    alureStreamSizeIsMicroSec(AL_TRUE);
    mHandle = alureCreateStreamFromMemory(data, length, 250000, 0, NULL);
}

alureStream* Stream::get() {
    return mHandle;
}

