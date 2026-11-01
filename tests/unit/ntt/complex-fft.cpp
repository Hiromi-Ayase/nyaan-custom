// Verify: ntt/complex-fft.hpp
// 整数・実数・15bit分割の畳み込みを直接積と比較する。負の係数とFFTへの切替前後を含む。
#include <bits/stdc++.h>
using namespace std;
#include "ntt/complex-fft.hpp"

int main() {
  using FFT = ArbitraryModConvolution::CooleyTukey;
  mt19937 rng(9043);
  for (int n : {1, 2, 39, 40, 41, 63, 64, 65, 129, 257}) {
    for (int m : {1, 40, 41, 128, 257}) {
      vector<int> a(n);
      vector<int> b(m);
      for (auto& x : a) {
        x = int(rng() % 20001) - 10000;
      }
      for (auto& x : b) {
        x = int(rng() % 20001) - 10000;
      }
      vector<long long> expected(n + m - 1);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          expected[i + j] += 1LL * a[i] * b[j];
        }
      }
      // 正負の整数係数が、複素FFTの丸めを経ても二重ループの積と一致する。
      assert(FFT::multiply(a, b) == expected);

      vector<double> da(a.begin(), a.end());
      vector<double> db(b.begin(), b.end());
      for (auto& x : da) {
        x /= 8;
      }
      auto got = FFT::multiply(da, db);
      for (int k = 0; k < (int)got.size(); ++k) {
        // 実数版は係数を1/8にした積を返し、絶対誤差も十分小さい。
        assert(abs(got[k] - expected[k] / 8.0) < 1e-4);
      }

      for (auto& x : a) {
        x = rng() % 1000000007;
      }
      for (auto& x : b) {
        x = rng() % 1000000007;
      }
      vector<int> modular(n + m - 1);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          modular[i + j] = (modular[i + j] + 1LL * a[i] * b[j]) % 1000000007;
        }
      }
      // 係数を15bitに分割する版を、大きな係数の直接剰余計算と比較する。
      assert(FFT::multiply_15bit<1000000007>(a, b) == modular);
    }
  }
}
