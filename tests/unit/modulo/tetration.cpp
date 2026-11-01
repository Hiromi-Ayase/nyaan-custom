// Verify: modulo/tetration.hpp
// 値を通常の整数で構築できる高さの累乗塔について、構築後に法を取った値と比較する。
// 法1、非互いに素の底、0と1の高い塔、0^0=1の規約を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "modulo/tetration.hpp"

int main() {
  for (unsigned a = 0; a <= 5; ++a) {
    unsigned long long tower = 1;
    for (int height = 0; height <= 5; ++height) {
      for (unsigned mod = 1; mod <= 300; ++mod) {
        // 整数として計算できる小さな冪塔を実際に作り、最後に剰余を取った値と比較する。
        assert(tetration(a, height, mod) == tower % mod);
      }

      __uint128_t next = 1;
      if (a >= 2 && tower > 63) {
        break;
      }

      for (unsigned long long e = 0; e < tower; ++e) {
        next *= a;
        if (next > ULLONG_MAX) {
          break;
        }
      }

      if (next > ULLONG_MAX) {
        break;
      }

      tower = next;
    }
  }

  for (unsigned m = 1; m <= 300; ++m) {
    // 底0では0^0=1として、高さが偶数なら1になる。法1の場合も確認する。
    assert(tetration(0, 1000000, m) == 1 % m);

    // 底0で高さが奇数なら0になる。巨大な高さでも偶奇を取り違えない。
    assert(tetration(0, 1000001, m) == 0);

    // 底1なら高さによらず1となり、法1の場合の答えは0になる。
    assert(tetration(1, 1000000, m) == 1 % m);
  }
}
