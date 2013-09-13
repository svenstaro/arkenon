#include "Listener.hpp"
#include "util/check.hpp"

Listener::Listener(const std::string& name) 
	: Node(name) 
{
	ALfloat listenerVel[]={0.0,0.0,0.0};
	alListenerfv(AL_VELOCITY, listenerVel); 	// Velocity ...
}

void Listener::setGlobalVolume(float  vol) {
	alListenerf(AL_GAIN, vol * 0.01f);
}

void Listener::onUpdate(double dt)  {
	alureUpdate();

	glm::vec3 pos = getAbsolutePosition();
	alListener3f(AL_POSITION, pos.x, pos.y, pos.z);

	glm::vec3 dir = getAbsoluteRotation() * glm::vec3(0.0,0.0,-1.0);
	float orientation[] = {dir.x, dir.y, dir.z, 0.f, 1.f, 0.f};
	alListenerfv(AL_ORIENTATION, orientation);

	glm::vec3 velocity = glm::vec3((pos - mPrevPos) / (float)dt);

	alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	mPrevPos = pos;


	//std::cout <<  dir.x  << " " << dir.y << " " << dir.z << std::endl;
}