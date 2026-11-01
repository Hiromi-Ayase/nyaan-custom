// Verify: matrix/hafnian.hpp
// 残った最小の頂点の相手を全て試して完全マッチングを列挙し、重みの積の総和を比較する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "modint/modint.hpp"
#include "matrix/hafnian.hpp"

using M = ModInt<101>;

M enumerate(const vector<vector<M>>& a, int mask) {
  if (!mask) {
    return 1;
  }
  int i = __builtin_ctz(mask);
  mask ^= 1 << i;
  M sum = 0;
  for (int j = i + 1; j < (int)a.size(); ++j) {
    if (mask >> j & 1) {
      sum += a[i][j] * enumerate(a, mask ^ (1 << j));
    }
  }
  return sum;
}

int main() {
  mt19937 rng(607);
  for (int n = 0; n <= 10; n += 2) {
    for (int trial = 0; trial < 40; ++trial) {
      vector<vector<M>> a(n, vector<M>(n));
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
          a[i][j] = trial == 0 ? 0 : trial == 1 ? 1 : rng() % 101;
          a[j][i] = a[i][j];
        }
      }
      // 0頂点の空マッチング、全0、全1、ランダムな対称行列を全列挙の答えと比較する。
      assert(Hafnian(a) == enumerate(a, (1 << n) - 1));
    }
  }
}
