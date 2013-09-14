#include "StreamedSound.hpp"
#include <iostream>

#define NUM_BUFFERS 3

StreamedSound::StreamedSound(const std::string& name)
    : SoundSource(name) {}

StreamedSound::StreamedSound(const std::string& name, std::shared_ptr<Stream> stream)
    : SoundSource(name)
{
    setStream(stream);
}

StreamedSound::~StreamedSound() {
    stop();
}

void StreamedSound::setStream(std::shared_ptr<Stream> stream) {
    if(mStream) {
        stop();
    }
    mStream = stream;
}

std::shared_ptr<Stream> StreamedSound::getStream() {
    return mStream;
}

void StreamedSound::play() {
    alurePlaySourceStream(mHandle, mStream->get(), NUM_BUFFERS, mLooping ? -1 : 0, [](void *userdata, ALuint source) { ((StreamedSound*)userdata)->donePlaying(); }, this);
}

void StreamedSound::stop() {
    alureStopSource(mHandle, AL_FALSE);
}

void StreamedSound::pause() {
    alurePauseSource(mHandle);
}

void StreamedSound::resume() {
    alureResumeSource(mHandle);
}

void StreamedSound::donePlaying() {

}

void StreamedSound::setLoop(bool loop) {
    mLooping = loop;
}