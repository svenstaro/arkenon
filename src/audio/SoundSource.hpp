#ifndef _AUDIO_SOUNDSOURCE_HPP
#define _AUDIO_SOUNDSOURCE_HPP

#include <memory>
#include "scene/Node.hpp"
#include "audio/Listener.hpp"

class SoundSource : public Node {
public:
	enum Status {
		Playing,
		Paused,
		Stopped
	};

    SoundSource(const std::string& name);
    ~SoundSource();

    void onUpdate(double dt);

    virtual void play();
    virtual void stop();
    virtual void pause();

	void setVolume(float volume);
	void setPitch(float pitch);
	void setRelativeToListener(bool rel);
	void setLoop(bool loop);

	Status getStatus();
private:
	glm::vec3 mPrevPos;
protected:
	ALuint mHandle;
};

#endif
