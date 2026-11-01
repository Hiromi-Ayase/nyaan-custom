// Verify: data-structure-2d/wavelet-matrix.hpp
// 区間をコピーしてソートし、k番目・頻度・直前/直後を確認する。ビット列は全prefixを直接数える。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure-2d/wavelet-matrix.hpp"

// int/long longと符号なし型の最大値付近を、区間の直接走査と比較する。
template <typename T>
void check_limits() {
  T largest = numeric_limits<T>::max();
  vector<T> a{largest / 2 + 1, 0, largest, 1, largest - 1};
  vector<T> thresholds{0, 1, 2, largest / 2, largest / 2 + 1, largest - 1, largest};
  if constexpr (is_signed_v<T>) {
    thresholds.push_back(-1);
    thresholds.push_back(numeric_limits<T>::min());
  }
  WaveletMatrix<T> tree(a);
  for (int i = 0; i < (int)a.size(); ++i) {
    // 最上位の値ビットを使う要素も、元の位置から取得できる。
    assert(tree.access(i) == a[i]);
  }
  for (int l = 0; l <= (int)a.size(); ++l) {
    for (int r = l; r <= (int)a.size(); ++r) {
      vector<T> sorted(a.begin() + l, a.begin() + r);
      sort(sorted.begin(), sorted.end());
      for (int k = 0; k < r - l; ++k) {
        // 順序統計も符号ビット付近の値で並び順を失わない。
        assert(tree.kth_smallest(l, r, k) == sorted[k]);
      }
      for (T upper : thresholds) {
        int count = 0;
        T previous = T(-1);
        T next = T(-1);
        bool found_next = false;
        for (T x : sorted) {
          if (x < upper) {
            ++count;
            previous = x;
          } else if (!found_next) {
            next = x;
            found_next = true;
          }
        }
        // 負の閾値、0、最大値でも頻度と直前・直後の値は直接走査に一致する。
        assert(tree.range_freq(l, r, upper) == count);
        assert(tree.prev_value(l, r, upper) == previous);
        assert(tree.next_value(l, r, upper) == next);
        for (T lower : thresholds) {
          if (lower > upper) {
            continue;
          }
          int expected = 0;
          for (T x : sorted) {
            expected += lower <= x && x < upper;
          }
          // 二つの閾値による半開値域の頻度も直接数える。
          assert(tree.range_freq(l, r, lower, upper) == expected);
        }
      }
    }
  }
}

int main() {
  check_limits<int>();
  check_limits<long long>();
  check_limits<unsigned int>();
  check_limits<unsigned long long>();

  mt19937_64 rng(1904);
  for (int n : {1, 2, 3, 31, 63, 64, 65, 127, 128, 129, 257}) {
    bit_vector bits(n);
    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
      values[i] = rng() % 2;
      if (values[i]) {
        bits.set(i);
      }
    }
    bits.build();
    int count = 0;
    for (int i = 0; i <= n; ++i) {
      // 64ビット語の境界を含め、rankは先頭iビットを1つずつ数えた値に一致する。
      assert(bits.rank1(i) == (unsigned)count && bits.rank0(i) == (unsigned)(i - count));
      if (i < n) {
        assert(bits.get(i) == (unsigned)values[i]);
        count += values[i];
      }
    }
    for (int trial = 0; trial < 3; ++trial) {
      vector<long long> a(n);
      for (auto& x : a) {
        x = trial == 0 ? 0 : trial == 1 ? rng() % 17 : rng() % ((1LL << 40) + 1);
      }
      WaveletMatrix<long long> tree(a);
      WaveletMatrix<long long> built(n);
      for (int i = 0; i < n; ++i) {
        built.set(i, a[i]);
      }
      built.build();
      for (int i = 0; i < n; ++i) {
        assert(tree.access(i) == a[i] && built.access(i) == a[i]);
      }
      for (int step = 0; step < 300; ++step) {
        int l = rng() % (n + 1);
        int r = rng() % (n + 1);
        if (l > r) {
          swap(l, r);
        }
        vector<long long> sorted(a.begin() + l, a.begin() + r);
        sort(sorted.begin(), sorted.end());
        if (l < r) {
          int k = rng() % (r - l);
          assert(tree.kth_smallest(l, r, k) == sorted[k] &&
                 tree.kth_largest(l, r, k) == sorted[r - l - 1 - k]);
        }
        long long lower = rng() % ((1LL << 41) + 1);
        long long upper = rng() % ((1LL << 41) + 1);
        if (trial < 2) {
          lower %= 20;
          upper %= 20;
        }
        if (lower > upper) {
          swap(lower, upper);
        }
        int frequency = 0;
        long long previous = -1;
        long long next = -1;
        for (auto x : sorted) {
          if (lower <= x && x < upper) {
            ++frequency;
          }
          if (x < upper) {
            previous = x;
          }
          if (x >= lower && next == -1) {
            next = x;
          }
        }
        // 閾値が全値より小さい/大きい場合と、該当なしの-1も確認する。
        assert(tree.range_freq(l, r, lower, upper) == frequency);
        assert(tree.prev_value(l, r, upper) == previous && tree.next_value(l, r, lower) == next);
      }
    }
  }
}
