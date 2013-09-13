#include "Buffer.hpp"
#include <iostream>
#include "util/check.hpp"

Buffer::Buffer() {
	alGenBuffers(1, &mHandle);
	AL_CHECK();
}

Buffer::~Buffer() {
	alDeleteBuffers(1, &mHandle);
}

void Buffer::loadFromFile(const std::string& path) {
	std::cout << "Loading " << path << std::endl;
	alureBufferDataFromFile(path.c_str(), mHandle);
}

void Buffer::loadFromMemory(const ALubyte *data, ALsizei length) {
	alureBufferDataFromMemory(data, length, mHandle);
}

ALuint Buffer::get() {
	return mHandle;
}

