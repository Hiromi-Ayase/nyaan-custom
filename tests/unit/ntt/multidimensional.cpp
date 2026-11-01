// Verify: ntt/multidimensional-ntt.hpp
// Verify: ntt/multivariate-circular-convolution.hpp
// 混合基数の添字を各軸へ展開し、多次元DFTの定義と巡回する添字和による直接積と比較する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/modint.hpp"
#include "fps/arbitrary-fps.hpp"
#include "ntt/multidimensional-ntt.hpp"
#include "ntt/multivariate-circular-convolution.hpp"

using M = ModInt<1000000007>;
using F = FormalPowerSeries<M>;

int main() {
  mt19937 rng(9046);
  const double pi = acos(-1.0);
  for (vector<int> base : vector<vector<int>>{{1}, {2}, {3, 5}, {2, 3, 4}, {1, 7, 1}}) {
    int n = accumulate(base.begin(), base.end(), 1, multiplies<int>());
    vector<complex<double>> a(n);
    for (auto& x : a) {
      x = {double(int(rng() % 21) - 10), double(int(rng() % 21) - 10)};
    }
    auto dft = [pi](vector<complex<double>>& f, bool reverse) {
      int size = f.size();
      vector<complex<double>> g(size);
      for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
          g[i] += f[j] * polar(1.0, (reverse ? -1 : 1) * 2 * pi * i * j / size);
        }
        if (reverse) {
          g[i] /= size;
        }
      }
      f = g;
    };
    MultidimensionalFourierTransform<complex<double>> fft(base, dft);
    vector<complex<double>> expected(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int x = i;
        int y = j;
        double angle = 0;
        for (int radix : base) {
          angle += 2 * pi * (x % radix) * (y % radix) / radix;
          x /= radix;
          y /= radix;
        }
        expected[i] += a[j] * polar(1.0, angle);
      }
    }
    auto got = a;
    fft.fft(got);
    for (int i = 0; i < n; ++i) {
      // 全軸の角度を直接足した多次元DFTと比べ、軸の順序やストライドを確認する。
      assert(abs(got[i] - expected[i]) < 1e-8);
    }
    fft.fft(got, true);
    for (int i = 0; i < n; ++i) {
      // 逆方向に各軸を処理して、元の配列を誤差内で復元できる。
      assert(abs(got[i] - a[i]) < 1e-8);
    }

    F f(n);
    F g(n);
    for (auto& x : f) {
      x = rng() % M::get_mod();
    }
    for (auto& x : g) {
      x = rng() % M::get_mod();
    }
    F product(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int x = i;
        int y = j;
        int dest = 0;
        int stride = 1;
        for (int radix : base) {
          dest += ((x % radix + y % radix) % radix) * stride;
          stride *= radix;
          x /= radix;
          y /= radix;
        }
        product[dest] += f[i] * g[j];
      }
    }
    // 各軸ごとに次数を巡回させる直接積と比較し、CRT復元までを検証する。
    assert(multivariate_circular_convolution(f, g, base) == product);
  }
}
