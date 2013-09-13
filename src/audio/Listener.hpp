#ifndef _AUDIO_LISTENER_HPP
#define _AUDIO_LISTENER_HPP

#include <AL/al.h>
#include <AL/alc.h>
#include <memory>
#include "scene/Node.hpp"
#include "audio/AudioDevice.hpp"

class Listener : public Node {
public:
    Listener(const std::string& name);
    void setGlobalVolume(float vol);

    void onUpdate(double dt);
private:
	glm::vec3 mPrevPos;
};

#endif
