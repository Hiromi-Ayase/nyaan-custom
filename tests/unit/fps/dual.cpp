// Verify: fps/dual-fps.hpp
// 周波数領域で保持する多項式を、係数の筆算と比較する。サイズ変更と定数の特殊処理を含む。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
#include "fps/dual-fps.hpp"

fps multiply(const fps& a, const fps& b, int n) {
  fps result(n);
  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)b.size() && i + j < n; ++j) {
      result[i + j] += a[i] * b[j];
    }
  }
  return result;
}

fps normalized(fps a) {
  while (!a.empty() && a.back() == 0) {
    a.pop_back();
  }
  return a;
}

int main() {
  mt19937 rng(2112);
  for (int n : {0, 1, 2, 3, 4, 5, 16, 17, 64, 65, 129}) {
    for (int m : {0, 1, 2, 3, 7, 32, 33}) {
      fps a(n);
      fps b(m);
      for (auto& c : a) {
        c = rng();
      }
      for (auto& c : b) {
        c = rng();
      }
      DualFPS<fps> left(a);
      DualFPS<fps> right(b);
      // 内部の埋め草を取り除いた係数列が、入力と一致する。
      assert(normalized(left.get()) == normalized(a));
      fps sum(max(n, m));
      fps difference(max(n, m));
      for (int i = 0; i < (int)sum.size(); ++i) {
        mint x = i < n ? a[i] : mint(0);
        mint y = i < m ? b[i] : mint(0);
        sum[i] = x + y;
        difference[i] = x - y;
      }
      assert(normalized((left + right).get()) == normalized(sum));
      assert(normalized((left - right).get()) == normalized(difference));
      assert(normalized((left * right).get()) == normalized(multiply(a, b, max(0, n + m - 1))));
      auto accumulated = left;
      accumulated += right;
      accumulated *= right;
      // 既にNTT長を拡張したオブジェクトの再利用と複合代入も検査する。
      assert(normalized(accumulated.get()) == normalized(multiply(sum, b, sum.size() + b.size())));
      for (int shift : {0, 1, 7, 33}) {
        fps shifted(shift, 0);
        shifted.insert(shifted.end(), a.begin(), a.end());
        assert(normalized((left << shift).get()) == normalized(shifted));
      }
      assert(normalized((left * mint(0)).get()).empty());
    }
  }
}
