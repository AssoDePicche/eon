#include "between.h"

#include <random>

using std::mt19937;
using std::random_device;
using std::uniform_real_distribution;

float between(const float min, const float max) {
  static random_device device;

  static mt19937 mersenne_twister(device());

  static uniform_real_distribution<float> distribution(min, max);

  return distribution(mersenne_twister);
}
