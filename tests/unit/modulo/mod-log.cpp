// Verify: modulo/mod-log.hpp
// a^kをk=0から順に計算し、最初に同じ剰余へ戻るまでに現れる最小指数を期待値にする。
// 法1、合成数、a=0、逆元を持たない底、負の底と目標を含め全小規模ケースを確認する。
#include <bits/stdc++.h>
using namespace std;
#include "modulo/mod-log.hpp"

int main() {
  for (int mod = 1; mod <= 100; ++mod) {
    for (int a = 0; a < mod; ++a) {
      vector<int> first(mod, -1);
      int value = 1 % mod;
      int exponent = 0;
      while (first[value] < 0) {
        first[value] = exponent++;
        value = value * a % mod;
      }

      for (int b = 0; b < mod; ++b) {
        // 剰余が循環するまでaを掛け続けて記録した、bに初めて到達する指数と比較する。
        assert(mod_log(a, b, mod) == first[b]);

        // 底と目標値を負の代表元に置き換えても、最小指数は変わらない。
        assert(mod_log(a - mod, b - mod, mod) == first[b]);
      }
    }
  }
}
