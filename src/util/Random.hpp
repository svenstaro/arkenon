#ifndef _UTIL_RANDOM_HPP
#define _UTIL_RANDOM_HPP

#include <vector>
#include <stdlib.h>
#include <random>
#include <iostream>

class Random {
public:
    Random(unsigned int seed);

    //void fillWithRandom(unsigned int num, std::vector<unsigned char>& vec);
    void fillWithRandom(unsigned int num, std::vector<float>& vec);

private:
	std::mt19937 mRng;
};

#endif
