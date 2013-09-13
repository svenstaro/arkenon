#ifndef _AUDIO_SOUND_HPP
#define _AUDIO_SOUND_HPP

#include <memory>
#include "audio/SoundSource.hpp"
#include "audio/Listener.hpp"
#include "audio/Buffer.hpp"

class Sound : public SoundSource {
public:
	Sound(const std::string& name);
    Sound(const std::string& name, std::shared_ptr<Buffer> buffer);
    ~Sound();
    void play();
    void stop();
    void pause();
    void resume();

    void setBuffer(std::shared_ptr<Buffer> buffer);
    std::shared_ptr<Buffer> getBuffer();
private:
	void donePlaying();

	std::shared_ptr<Buffer> mBuffer;
};

#endif
