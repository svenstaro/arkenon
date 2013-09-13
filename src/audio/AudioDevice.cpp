#include "AudioDevice.hpp"
#include <iostream>
#include "util/check.hpp"

AudioDevice::AudioDevice() {
	if(!alureInitDevice(NULL, NULL)) {
		std::cerr << "Error: OpenAl cannot initialize Device" << std::endl;
	}
	AL_CHECK();
	
	std::cout << "initialized audio device" << std::endl;
}

AudioDevice::~AudioDevice() {
	alureShutdownDevice();
}
