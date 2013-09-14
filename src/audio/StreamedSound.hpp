#ifndef _AUDIO_STREAMEDSOUND_HPP
#define _AUDIO_STREAMEDSOUND_HPP

#include <memory>
#include "audio/SoundSource.hpp"
#include "audio/Listener.hpp"
#include "audio/Stream.hpp"

class StreamedSound : public SoundSource {
public:
    StreamedSound(const std::string& name);
    StreamedSound(const std::string& name, std::shared_ptr<Stream> stream);
    ~StreamedSound();
    void play();
    void stop();
    void pause();
    void resume();

    void setLoop(bool loop);

    void setStream(std::shared_ptr<Stream> stream);
    std::shared_ptr<Stream> getStream();
private:
    void donePlaying();

    std::shared_ptr<Stream> mStream;
    bool mLooping;
};

#endif