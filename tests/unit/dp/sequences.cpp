// Verify: dp/inversion-counting.hpp
// Verify: dp/longest-increasing-sequence.hpp
// Verify: dp/maximal-rectangle.hpp
// 転倒数は全添字対、LISは全部分列、ヒストグラムの最大長方形は全区間を列挙して比較する。
// 隣接交換距離は目標の左端から一致する要素を移動する愚直操作で求める。LISは仕様上非空列を対象とする。
#include <bits/stdc++.h>
using namespace std;
#include "dp/inversion-counting.hpp"
#include "dp/longest-increasing-sequence.hpp"
#include "dp/maximal-rectangle.hpp"

int main() {
  mt19937 rng(973);
  for (int n = 0; n <= 12; ++n) {
    for (int trial = 0; trial < 80; ++trial) {
      vector<int> a(n);
      for (int& x : a) {
        x = int(rng() % 7) - 3;
      }

      long long inv = 0;
      for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
          inv += a[i] > a[j];
        }
      }

      // 全ての添字対を比較して数えた転倒数と一致する。重複値同士は数えない。
      assert(inversion_counting(a) == inv);
      auto b = a;
      shuffle(b.begin(), b.end(), rng);
      auto work = a;
      long long distance = 0;
      for (int i = 0; i < n; ++i) {
        int j = i;
        while (work[j] != b[i]) {
          ++j;
        }

        while (j > i) {
          swap(work[j], work[j - 1]);
          --j;
          ++distance;
        }
      }

      // 必要な要素を隣接交換で1つずつ移動した操作回数と比較する。
      assert(swap_distance(a, b) == distance);
      if (n) {
        b[0] = 100;

        // 要素の多重集合が異なる列同士は、隣接交換だけでは一致させられない。
        assert(swap_distance(a, b) == -1);
      }

      if (n) {
        int longest = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
          int last = INT_MIN;
          int size = 0;
          bool ok = true;
          for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
              ok &= last < a[i];
              last = a[i];
              ++size;
            }
          }

          if (ok) {
            longest = max(longest, size);
          }
        }

        auto indices = longest_increasing_sequence(a);

        // 返された部分列の長さを、全ての添字部分集合から求めた厳密増加列の最大長と比べる。
        assert((int)indices.size() == longest);
        for (int i = 0; i < (int)indices.size(); ++i) {
          // 復元された各添字は、元の配列の範囲内にある。
          assert(0 <= indices[i] && indices[i] < n);
          if (i) {
            // 復元した添字が左から右に並び、対応する値も厳密に増加する。
            assert(indices[i - 1] < indices[i] && a[indices[i - 1]] < a[indices[i]]);
          }
        }
      }

      vector<long long> height(n);
      for (int i = 0; i < n; ++i) {
        height[i] = a[i] + 3;
      }

      long long rectangle = 0;
      for (int l = 0; l < n; ++l) {
        for (int r = l + 1; r <= n; ++r) {
          rectangle =
              max(rectangle, (r - l) * *min_element(height.begin() + l, height.begin() + r));
        }
      }

      // 全区間の「幅×区間最小高さ」を列挙した最大長方形の面積と比較する。
      assert(MaximalRectangle(height) == rectangle);
    }
  }
}
