// Verify: set-function/enumerate-set.hpp
// Verify: set-function/zeta-mobius-transform.hpp
// Verify: set-function/walsh-hadamard-transform.hpp
// Verify: set-function/and-convolution.hpp
// Verify: set-function/or-convolution.hpp
// Verify: set-function/xor-convolution.hpp
// Verify: set-function/subset-convolution.hpp
// 全ての部分集合対を列挙し、AND/OR/XOR/非交差集合の畳み込みを定義通り計算する。
// zetaとHadamardは変換式を直接計算し、逆変換後の復元も確認する。空の台集合、負の係数、ゼロ列を含む。
#include <bits/stdc++.h>
using namespace std;
#include "set-function/enumerate-set.hpp"
#include "set-function/zeta-mobius-transform.hpp"
#include "set-function/walsh-hadamard-transform.hpp"
#include "set-function/and-convolution.hpp"
#include "set-function/or-convolution.hpp"
#include "set-function/xor-convolution.hpp"
#include "set-function/subset-convolution.hpp"

int main() {
  mt19937 rng(632);
  SubsetConvolution<long long, 8> subset;
  for (int bits = 0; bits <= 8; ++bits) {
    for (int trial = 0; trial < 12; ++trial) {
      int n = 1 << bits;
      vector<long long> a(n);
      vector<long long> b(n);
      for (auto& x : a) {
        x = trial == 0 ? 0 : int(rng() % 11) - 5;
      }

      for (auto& x : b) {
        x = int(rng() % 11) - 5;
      }

      vector<long long> an(n);
      vector<long long> o(n);
      vector<long long> x(n);
      vector<long long> sub(n);
      vector<long long> zsub(n);
      vector<long long> zsuper(n);
      vector<long long> had(n);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          an[i & j] += a[i] * b[j];
          o[i | j] += a[i] * b[j];
          x[i ^ j] += a[i] * b[j];
          if (!(i & j)) {
            sub[i | j] += a[i] * b[j];
          }

          if ((i & j) == j) {
            zsub[i] += a[j];
          }

          if ((i & j) == i) {
            zsuper[i] += a[j];
          }

          had[i] += (__builtin_parity(i & j) ? -1 : 1) * a[j];
        }
      }

      // AND・OR・XORの行き先へ全ての添字対の積を足した畳み込みと比較する。
      assert(and_convolution(a, b) == an && or_convolution(a, b) == o &&
             xor_convolution(a, b) == x);

      // 共通ビットがない添字対だけを全列挙した部分集合畳み込みと比較する。
      assert(subset.multiply(a, b) == sub);
      auto s = a;
      subset_zeta_transform(s);

      // 部分集合ゼータ変換を、各マスクの全部分集合を直接足した結果と比較する。
      assert(s == zsub);
      subset_mobius_transform(s);

      // 部分集合メビウス変換を続けて適用すると、元の列に戻る。
      assert(s == a);
      s = a;
      superset_zeta_transform(s);

      // 上位集合ゼータ変換を、各マスクを含む全マスクの直接和と比較する。
      assert(s == zsuper);
      superset_mobius_transform(s);

      // 上位集合メビウス変換を続けて適用すると、元の列に戻る。
      assert(s == a);
      s = a;
      walsh_hadamard_transform(s);

      // Walsh-Hadamard変換を、共通ビット数の偶奇から符号を決めた直接和と比較する。
      assert(s == had);
      walsh_hadamard_transform(s, true);

      // 逆Walsh-Hadamard変換は、長さによる正規化も含めて元の列に戻る。
      assert(s == a);
      for (int mask = 0; mask < n; ++mask) {
        vector<int> lower;
        vector<int> upper;
        for (int j = 0; j < n; ++j) {
          if ((j & mask) == j) {
            lower.push_back(j);
          }

          if ((j & mask) == mask) {
            upper.push_back(j);
          }
        }

        auto got = enumerate_subset(mask);
        sort(got.begin(), got.end());

        // 部分集合の列挙結果に漏れ・重複がなく、ビット条件で全探索した集合と一致する。
        assert(got == lower);

        // 上位集合の列挙結果を、包含条件で全マスクを調べた列と比較する。
        assert(enumerate_superset(mask, bits) == upper);
      }
    }
  }
}
