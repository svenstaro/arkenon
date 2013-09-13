#include "SoundSource.hpp"

SoundSource::SoundSource(const std::string& name) 
	: Node(name)
{
	alGenSources(1, &mHandle);
	alSourcei(mHandle, AL_BUFFER, 0);
}

SoundSource::~SoundSource() {
	alSourcei(mHandle, AL_BUFFER, 0);
	alDeleteSources(1, &mHandle);
}

void SoundSource::onUpdate(double dt) {
	glm::vec3 pos = getAbsolutePosition();
	alSource3f(mHandle, AL_POSITION, pos.x, pos.y, pos.z);

	glm::vec3 velocity = glm::vec3((pos - mPrevPos) / (float)dt);

	alSource3f(mHandle, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	mPrevPos = pos;
}

void SoundSource::play() {
	alSourcePlay(mHandle);
}
void SoundSource::stop() {
	alSourceStop(mHandle);
}
void SoundSource::pause() {
	alSourcePause(mHandle);
}

void SoundSource::setVolume(float volume) {
	alSourcef(mHandle, AL_GAIN, volume * 0.01f);
}

void SoundSource::setPitch(float pitch) {
	alSourcef(mHandle, AL_PITCH, pitch);
}

void SoundSource::setRelativeToListener(bool rel) {
	alSourcei(mHandle, AL_SOURCE_RELATIVE, rel);
}

void SoundSource::setLoop(bool loop) {
	alSourcei(mHandle, AL_LOOPING, loop);
}

SoundSource::Status SoundSource::getStatus() {
	ALint status;
	alGetSourcei(mHandle, AL_SOURCE_STATE, &status);

	switch(status) {
		case AL_INITIAL:
		case AL_STOPPED: return Stopped;
		case AL_PAUSED: return Paused;
		case AL_PLAYING: return Playing;
	}
	return Stopped;
}
