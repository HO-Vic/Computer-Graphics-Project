#include<random>

float RandomFl(float x, float y) {
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_real_distribution<float> dis(x, y);
	return dis(gen);
}

int RandomIN(int x, int y) {
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<int> dis(x, y);
	return dis(gen);
}