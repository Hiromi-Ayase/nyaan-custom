// Verify: modint/adjunction-modint.hpp
// 拡大体の係数を整数の組で持ち、(a+b√3)(c+d√3)を手計算した結果と比較する。
// 小さい素数法17で全係数を列挙し、非零元の逆元と小さい指数の累乗も確認する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/modint.hpp"
#include "modint/adjunction-modint.hpp"

int main() {
  using M = ModInt<17>;
  using A = Adjunction<M, 3>;
  auto norm = [](int x) {
    x %= 17;
    return x < 0 ? x + 17 : x;
  };
  for (int a = 0; a < 17; ++a) {
    for (int b = 0; b < 17; ++b) {
      A x{M(a), M(b)};
      for (int c = 0; c < 17; ++c) {
        for (int d = 0; d < 17; ++d) {
          A y{M(c), M(d)};
          A sum = x + y;
          A diff = x - y;
          A product = x * y;

          // a+b√3の加算は、定数項と√3の係数を独立に足した値になる。
          assert(sum.a.get() == norm(a + c) && sum.b.get() == norm(b + d));

          // a+b√3の減算は、両係数を独立に引いて正規化した値になる。
          assert(diff.a.get() == norm(a - c) && diff.b.get() == norm(b - d));

          // 積の定数項はac+3bdとなり、√3の2乗が3として扱われる。
          assert(product.a.get() == norm(a * c + 3 * b * d));

          // 積の√3の係数はad+bcになる。
          assert(product.b.get() == norm(a * d + b * c));
        }
      }

      if (a || b) {
        // 0でない拡大体の要素に逆元を掛けると、乗法単位元1になる。
        assert(x * x.inverse() == A{1LL});
      }

      int u = 1;
      int v = 0;
      for (int e = 0; e <= 10; ++e) {
        auto y = x.pow(e);

        // 冪の両係数を、係数の組を逐次乗算して作った期待値と比較する。
        assert(y.a.get() == u && y.b.get() == v);
        int nu = norm(u * a + 3 * v * b);
        int nv = norm(u * b + v * a);
        u = nu;
        v = nv;
      }
    }
  }
}
