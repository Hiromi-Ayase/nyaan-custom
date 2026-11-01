// Verify: fps/multipoint-evaluation.hpp
// Verify: fps/polynomial-interpolation.hpp
// Verify: fps/fast-multieval.hpp
// Verify: fps/fast-interpolate.hpp
// 各点でのHorner法を正解とし、異なる点から元の全係数が復元されることを確認する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
using mint = LazyMontgomeryModInt<998244353>;
using fps = FormalPowerSeries<mint>;
#include "fps/multipoint-evaluation.hpp"
#include "fps/polynomial-interpolation.hpp"
#include "fps/fast-multieval.hpp"
#include "fps/fast-interpolate.hpp"

mint evaluate(const fps& f, mint x) {
  mint result = 0;
  for (int i = int(f.size()) - 1; i >= 0; --i) {
    result = result * x + f[i];
  }
  return result;
}

int main() {
  mt19937 rng(2103);
  for (int n : {1, 2, 3, 7, 16, 31, 32, 33, 64, 65, 129, 257}) {
    vector<mint> xs(n);
    for (int i = 0; i < n; ++i) {
      xs[i] = mint(i) * 1234567;
    }
    shuffle(xs.begin(), xs.end(), rng);
    SubproductTree<mint> tree(xs);
    for (int size : {0, 1, n, 2 * n + 3}) {
      fps f(size);
      for (auto& c : f) {
        c = rng();
      }
      vector<mint> ys(n);
      for (int i = 0; i < n; ++i) {
        ys[i] = evaluate(f, xs[i]);
      }
      // 定数・零多項式・点数より高い次数を含め、すべての評価値を独立に比較する。
      assert(MultipointEvaluation(f, xs) == ys);
      assert(FastMultiEval(f, xs) == ys);
      assert(tree.multiEval(f) == ys);
      if (size <= n) {
        // n点で次数n未満の多項式を一意に復元できる。
        assert(PolynomialInterpolation(xs, ys).pre(n) == f.pre(n));
        assert(tree.interpolate(ys).pre(n) == f.pre(n));
      }
    }
    fill(xs.begin(), xs.end(), mint(7));
    fps f{3, 4, 5};
    // 評価のみなら同じ点を繰り返してもよい。
    assert(MultipointEvaluation(f, xs) == vector<mint>(n, evaluate(f, 7)));
    assert(FastMultiEval(f, xs) == vector<mint>(n, evaluate(f, 7)));
  }
  assert(MultipointEvaluation(fps{1}, vector<mint>{}).empty());
  assert(FastMultiEval(fps{1}, vector<mint>{}).empty());
}
