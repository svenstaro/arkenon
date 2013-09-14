#include "Sound.hpp"
#include <iostream>

Sound::Sound(const std::string& name)
	: SoundSource(name) {}

Sound::Sound(const std::string& name, std::shared_ptr<Buffer> buffer)
	: SoundSource(name)
{
	setBuffer(buffer);
}

Sound::~Sound() {
	stop();
}

void Sound::setBuffer(std::shared_ptr<Buffer> buffer) {
	if(mBuffer) {
		stop();
	}
	mBuffer = buffer;
	alSourcei(mHandle, AL_BUFFER, mBuffer->get());
}

std::shared_ptr<Buffer> Sound::getBuffer() {
	return mBuffer;
}

void Sound::play() {
	alurePlaySource(mHandle, [](void *userdata, ALuint source) { ((Sound*)userdata)->donePlaying(); }, this);
}

void Sound::stop() {
	alureStopSource(mHandle, AL_FALSE);
}

void Sound::pause() {
	alurePauseSource(mHandle);
}

void Sound::resume() {
	alureResumeSource(mHandle);
}

void Sound::donePlaying() {

}