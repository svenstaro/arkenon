#ifndef _AUDIO_STREAM_HPP
#define _AUDIO_STREAM_HPP

#include <AL/alure.h>
#include <memory>

class Stream {
public:
    Stream();
    ~Stream();

    void loadFromFile(const std::string& path);
    void loadFromMemory(const ALubyte *data, ALsizei length);
    alureStream* get();

private:
    alureStream* mHandle;
};

#endif