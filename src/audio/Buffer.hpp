#ifndef _AUDIO_BUFFER_HPP
#define _AUDIO_BUFFER_HPP

#include <AL/alure.h>
#include <memory>

class Buffer {
public:
    Buffer();
    ~Buffer();

    void loadFromFile(const std::string& path);
    void loadFromMemory(const ALubyte *data, ALsizei length);
    ALuint get();

private:
	ALuint mHandle;
};

#endif
