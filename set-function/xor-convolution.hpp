#pragma once

#include <type_traits>
#include <vector>
using namespace std;
#include "walsh-hadamard-transform.hpp"

template <typename T>
vector<T> xor_convolution(vector<T> a, vector<T> b) {
  walsh_hadamard_transform(a);
  walsh_hadamard_transform(b);
  for (int i = 0; i < (int)a.size(); i++) a[i] *= b[i];
  walsh_hadamard_transform(a, true);
  return a;
}

/**
 * @brief XOR Convoluion
 * @docs docs/set-function/xor-convolution.md
 */
