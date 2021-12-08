#include<random>

float RandomFl(float x, float y) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(x, y);
	return dis(gen);
}