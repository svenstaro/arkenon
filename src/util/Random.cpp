#include "Random.hpp"

Random::Random(unsigned int seed) 
{
	mRng.seed(seed);
}

void Random::fillWithRandom(unsigned int num, std::vector<float>& vec) {
	std::uniform_real_distribution<float> floatdist(0.0, 1.0);

	for(unsigned int i = 0; i < num; ++i) {
		vec.push_back(floatdist(mRng));
	}
	
}

/*
void Random::fillWithRandom(unsigned int num, std::vector<unsigned char>& vec) {
	u_int32_t r;
	for(unsigned int i = 0; i < num / 4; ++i) {
		r = rand();

		vec.push_back((unsigned char)(r));
		vec.push_back((unsigned char)(r >> 8));
		vec.push_back((unsigned char)(r >> 16));
		vec.push_back((unsigned char)(r >> 24));
	}

	unsigned int rest = num - (num/4) * 4;

	for(unsigned int j = 0; j < rest; ++j) {
		r = rand();
		vec.push_back((unsigned char)r);
	}
}
*/