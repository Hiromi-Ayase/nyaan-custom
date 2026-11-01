#pragma once

#include <cassert>
#include <vector>
using namespace std;
#include "zeta-mobius-transform.hpp"

template <typename T>
vector<T> and_convolution(vector<T> a, vector<T> b) {
  superset_zeta_transform(a);
  superset_zeta_transform(b);
  for (int i = 0; i < (int)a.size(); i++) a[i] *= b[i];
  superset_mobius_transform(a);
  return a;
}

/**
 * @brief AND Convoluion
 * @docs docs/set-function/and-convolution.md
 */
