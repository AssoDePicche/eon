#include "between.h"

#include <random>

using std::mt19937;
using std::random_device;
using std::uniform_real_distribution;

float between(const float start, const float end) {
  random_device device;

  mt19937 mersenne_twister(device());

  uniform_real_distribution<float> distribution(start, end);

  return distribution(mersenne_twister);
}
