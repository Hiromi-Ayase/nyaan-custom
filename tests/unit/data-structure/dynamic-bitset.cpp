// Verify: data-structure/dynamic-bitset.hpp
// bool配列を参照にし、点更新・反転・XORと前後の立っているビットの検索を比較する。
// 0,1,63,64,65などワード境界の前後、全0と全1、参照プロキシ経由の更新を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/dynamic-bitset.hpp"

int main() {
  mt19937 rng(9381);
  for (int n : {0, 1, 63, 64, 65, 127, 128, 129}) {
    BitSet bits(n);
    vector<int> a(n);
    for (int step = 0; step < 400; ++step) {
      if (n) {
        int i = rng() % n;
        int op = rng() % 5;
        if (op == 0) {
          bits.set(i);
          a[i] = 1;
        }

        if (op == 1) {
          bits.reset(i);
          a[i] = 0;
        }

        if (op == 2) {
          bits[i].flip();
          a[i] ^= 1;
        }

        if (op == 3) {
          int j = rng() % n;
          bits[i] = bits[j];
          a[i] = a[j];
        }

        if (op == 4) {
          BitSet other(n);
          for (int j = 0; j < n; ++j) {
            if (rng() % 2) {
              other.set(j);
              a[j] ^= 1;
            }
          }

          bits ^= other;
        }
      }

      // ビット更新やXORをしても、論理上のビット数は変わらない。
      assert(bits.size() == (size_t)n);
      for (int i = 0; i < n; ++i) {
        // 全ての位置について、素朴な0/1配列に施した同じ更新結果と照合する。
        assert(bits.test(i) == bool(a[i]));
      }

      for (int i = -1; i < n; ++i) {
        int j = i + 1;
        while (j < n && !a[j]) {
          ++j;
        }

        // 指定位置より後の最初の1を、右方向への走査結果と照合する。
        assert(bits._Find_next(i) == j);
      }

      for (int i = 0; i <= n; ++i) {
        int j = i - 1;
        while (j >= 0 && !a[j]) {
          --j;
        }

        // 指定位置より前の最後の1を、左方向への走査結果と照合する。
        assert(bits._Find_prev(i) == j);
      }
    }
  }
}
