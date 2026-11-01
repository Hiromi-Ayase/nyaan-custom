// Verify: fps/arbitrary-fps.hpp
// Verify: fps/kitamasa.hpp
// 基本演算を筆算と係数漸化式で比較し、2の冪の前後・先頭ゼロを検査する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/arbitrary-fps.hpp"
#include "fps/kitamasa.hpp"
using mint = LazyMontgomeryModInt<1000000007>;
using fps = FormalPowerSeries<mint>;

// 係数を全組み合わせで掛ける筆算。検査対象の畳み込みは使わない。
fps multiply(const fps& a, const fps& b, int n) {
  fps c(n);
  for (int i = 0; i < (int)a.size(); ++i) {
    for (int j = 0; j < (int)b.size() && i + j < n; ++j) {
      c[i + j] += a[i] * b[j];
    }
  }
  return c;
}

fps exponential(const fps& a, int n) {
  fps result(n);
  if (n > 0) {
    result[0] = 1;
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j <= i && j < (int)a.size(); ++j) {
      result[i] += mint(j) * a[j] * result[i - j];
    }
    result[i] /= i;
  }
  return result;
}

int main() {
  mt19937 rng(2101);
  for (int n : {1, 2, 3, 7, 16, 31, 64, 65, 127, 128, 129, 257}) {
    fps a(n);
    fps b(n / 2 + 1);
    for (auto& x : a) {
      x = rng();
    }
    for (auto& x : b) {
      x = rng();
    }
    // 空多項式との積と、NTTに切り替わる大きさの積を筆算と比較する。
    assert((a * fps{}).empty());
    assert(a * b == multiply(a, b, a.size() + b.size() - 1));
    fps sum(max(a.size(), b.size()));
    fps difference(sum.size());
    for (int i = 0; i < (int)sum.size(); ++i) {
      mint x = i < (int)a.size() ? a[i] : mint(0);
      mint y = i < (int)b.size() ? b[i] : mint(0);
      sum[i] = x + y;
      difference[i] = x - y;
    }
    // 長さが異なる加減算は不足する係数を0として扱う。
    assert(a + b == sum && a - b == difference);
    assert(a.integral().diff() == a);
    assert(((a << 3) >> 3) == a && (a >> n).empty());
    assert(a.pre(n + 3).size() == size_t(n + 3));
    mint x = rng();
    mint value = 0;
    for (int i = n - 1; i >= 0; --i) {
      value = value * x + a[i];
    }
    // 評価値はHorner法、点ごとの積は係数の直接積と比較する。
    assert(a.eval(x) == value);
    fps dot(b.size());
    for (int i = 0; i < (int)b.size(); ++i) {
      dot[i] = a[i] * b[i];
    }
    assert(a.dot(b) == dot);
    a[0] = 3;
    fps inverse = a.inv(n);
    fps one(n);
    one[0] = 1;
    // 逆数との筆算の積は、指定次数まで定数1になる。
    assert(multiply(a, inverse, n) == one);
    a[0] = 0;
    fps exp = exponential(a, n);
    assert(a.exp(n) == exp);
    // logの定義 exp(log f)=f を、独立した係数漸化式で確認する。
    a[0] = 1;
    assert(exponential(a.log(n), n) == a);
    for (int shift : {0, 1, 3}) {
      fps base = a;
      for (int i = 0; i < min(n, shift); ++i) {
        base[i] = 0;
      }
      fps power = one;
      for (int k = 0; k <= 5; ++k) {
        // 0乗・先頭ゼロを含む冪を、繰り返し筆算した結果と比較する。
        assert(base.pow(k, n) == power);
        power = multiply(power, base, n);
      }
    }
    b.back() = 7;
    fps quotient(n + 1);
    for (auto& c : quotient) {
      c = rng();
    }
    fps remainder(b.size() - 1);
    for (auto& c : remainder) {
      c = rng();
    }
    fps dividend = multiply(b, quotient, b.size() + quotient.size() - 1);
    for (int i = 0; i < (int)remainder.size(); ++i) {
      dividend[i] += remainder[i];
    }
    remainder.shrink();
    // 商と余りから作った被除数で、小次数/高速の除算双方を確認する。
    assert(dividend / b == quotient && dividend % b == remainder);
  }
  // ゼロ級数の正の冪と、次数0の出力を確認する。
  assert(fps(5).pow(7) == fps(5));
  assert(fps{1}.pow(0, 0).empty());
  for (int order : {1, 2, 7, 32}) {
    for (int numerator_size : {0, 1, order, order + 3}) {
      fps denominator(order + 1);
      for (auto& x : denominator) {
        x = rng();
      }
      denominator[0] = 2 + rng() % 100;
      denominator.back() = 3;
      fps numerator(numerator_size);
      for (auto& x : numerator) {
        x = rng();
      }
      fps expected(128);
      for (int i = 0; i < (int)expected.size(); ++i) {
        mint value = i < numerator_size ? numerator[i] : mint(0);
        for (int j = 1; j <= min(i, order); ++j) {
          value -= denominator[j] * expected[i - j];
        }
        expected[i] = value / denominator[0];
      }
      for (int k : {0, 1, 2, 17, 127}) {
        // Q[0]!=1の分数P/Qを逐次除算し、任意法版Bostan-Moriの係数と比較する。
        assert(LinearRecurrence(k, denominator, numerator) == expected[k]);
      }
    }
  }
  for (long long k : {0LL, 1LL, 2LL, 10LL, 1000000000000000000LL}) {
    // 1/(2-2x)の全係数は1/2。遠い項でも分母の定数項で正規化される。
    assert(LinearRecurrence(k, fps{2, -2}, fps{1}) == mint(2).inverse());
    // Qを定数倍しても、初期値から定まる等比数列は変わらない。
    assert(kitamasa(k, fps{2, -14}, fps{3}) == mint(3) * mint(7).pow(k));
  }
}
