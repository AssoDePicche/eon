#ifndef BETWEEN_H
#define BETWEEN_H

#include <random>

using std::mt19937;
using std::random_device;
using std::uniform_real_distribution;

double between(const double start, const double end) {
  random_device device;

  mt19937 mersenne_twister(device());

  uniform_real_distribution<double> distribution(start, end);

  return distribution(mersenne_twister);
}

#endif
