// Verify: math/sweep.hpp
// Verify: math/sweep-restore.hpp
// Verify: math/f2.hpp
// 全ての部分集合のXORを列挙し、基底・復元・直交補空間を照合する。二元多項式GCDは約数全探索で比べる。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "math/sweep.hpp"
#include "math/sweep-restore.hpp"
#include "math/f2.hpp"

set<unsigned> span(const vector<unsigned>& values) {
  set<unsigned> result{0};
  for (unsigned x : values) {
    auto copy = result;
    for (unsigned y : copy) {
      result.insert(x ^ y);
    }
  }
  return result;
}

unsigned remainder(unsigned a, unsigned b) {
  int degree = 31 - __builtin_clz(b);
  for (int i = 15; i >= degree; --i) {
    if (a >> i & 1) {
      a ^= b << (i - degree);
    }
  }
  return a;
}

int main() {
  mt19937 rng(722);
  for (int trial = 0; trial < 300; ++trial) {
    vector<unsigned> values;
    Basis<unsigned, 8> basis;
    Sweep<unsigned> restoring;
    set<unsigned> expected{0};
    for (int i = 0; i < 10; ++i) {
      unsigned x = rng() % 256;
      bool changed = !expected.count(x);
      // 新しい値が今の部分集合XORで作れないときだけ、独立な基底として追加される。
      assert(basis.add(x) == changed);
      restoring.add(x, i);
      values.push_back(x);
      expected = span(values);
      // 張る空間の大きさが2^rankになり、最大値も全列挙の末尾と一致する。
      assert((1U << basis.size()) == expected.size() && basis.get_max() == *expected.rbegin());
      for (unsigned target = 0; target < 256; ++target) {
        // 基底の所属判定は、全ての部分集合XORを列挙した集合への所属と一致する。
        assert(basis.test(target) == bool(expected.count(target)));
        auto [ok, ids] = restoring.restore(target);
        // 元の入力のIDを返す版も、同じ所属判定になる。
        assert(ok == bool(expected.count(target)));
        if (ok) {
          unsigned actual = 0;
          for (int id : ids) {
            // 復元に使うIDは登録済みで、範囲外の値を含まない。
            assert(0 <= id && id < (int)values.size());
            actual ^= values[id];
          }
          // 返されたIDの要素を実際にXORすると、問い合わせた値になる。
          assert(actual == target);
        }
      }
    }
    // 正規化された基底を再度全列挙しても、張る空間は変わらない。
    assert(span(basis.get_basis()) == expected);
    set<unsigned> perpendicular;
    for (unsigned x = 0; x < 256; ++x) {
      bool valid = true;
      for (unsigned y : values) {
        valid = valid && __builtin_parity(x & y) == 0;
      }
      if (valid) {
        perpendicular.insert(x);
      }
    }
    // 直交補空間の基底は、全入力との内積が0になるビット列を漏れなく生成する。
    assert(span(basis.orthogonal_complement()) == perpendicular);
    vector<unsigned> additional{unsigned(rng() % 256), unsigned(rng() % 256)};
    basis.merge(Basis<unsigned, 8>(additional));
    values.insert(values.end(), additional.begin(), additional.end());
    // 2つの基底のmergeは、元の入力列を合わせた部分集合XORと同じ空間を張る。
    assert(span(basis.get_basis()) == span(values));
  }

  for (int trial = 0; trial < 3000; ++trial) {
    unsigned a = rng() % 256;
    unsigned b = rng() % 256;
    unsigned expected = 0;
    if (a || b) {
      for (unsigned divisor = 1; divisor < 256; ++divisor) {
        if (remainder(a, divisor) == 0 && remainder(b, divisor) == 0) {
          expected = divisor;
        }
      }
    }
    // 全ての二元多項式で割り切れを調べた最大次数の共通約数と比較する。
    assert(gcd(bitset<16>(a), bitset<16>(b)).to_ulong() == expected);
  }
  for (int n = 0; n <= 8; ++n) {
    for (int trial = 0; trial < 100; ++trial) {
      BitMat<8, 8> matrix(n, 8);
      vector<unsigned> values(n);
      for (int i = 0; i < n; ++i) {
        values[i] = rng() % 256;
        matrix[i] = values[i];
      }
      auto copy = matrix;
      int rank = 0;
      auto expected = span(values);
      while ((1U << rank) < expected.size()) {
        ++rank;
      }
      // 高位・低位どちらから消去しても、行XORの全列挙で求めた階数と一致する。
      assert(Gauss(matrix, true) == rank);
      assert(Gauss(copy, false) == rank);
    }
  }
}
