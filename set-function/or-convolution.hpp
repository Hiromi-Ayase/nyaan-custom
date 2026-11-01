#pragma once

#include <cassert>
#include <vector>
using namespace std;
#include "zeta-mobius-transform.hpp"

template <typename T>
vector<T> or_convolution(vector<T> a, vector<T> b) {
  subset_zeta_transform(a);
  subset_zeta_transform(b);
  for (int i = 0; i < (int)a.size(); i++) a[i] *= b[i];
  subset_mobius_transform(a);
  return a;
}

/**
 * @brief OR Convoluion
 * @docs docs/set-function/or-convolution.md
 */
