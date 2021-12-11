#include<random>

float RandomFl(float x, float y) {
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_real_distribution<float> dis(x, y);
	return dis(gen);
}