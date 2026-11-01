// Verify: math/nimber.hpp
// Verify: math/nimber-to-field.hpp
// 小さいnim積をmexの定義で計算し、上位bitは体の演算則と基底変換で検証する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "math/nimber.hpp"
#include "math/nimber-to-field.hpp"

template <class N>
void check_field() {
  using U = decltype(N::x);
  constexpr int bits = sizeof(U) * 8;
  N generator = U(1) << (bits / 2);
  NimberToField<N> conversion(generator);
  N power = 1;
  for (int i = 0; i < bits; ++i) {
    U mask = U(1) << i;
    // 多項式基底のi番目はgenerator^iに対応し、逆変換すると1bitだけが立つ。
    assert(conversion.field2nimber(mask) == power);
    assert(conversion.nimber2field(power) == mask);
    power *= generator;
  }
  mt19937_64 rng(723 + bits);
  for (int trial = 0; trial < 1000; ++trial) {
    N a = U(rng());
    N b = U(rng());
    N c = U(rng());
    // 上位bitを含む任意の値でも、基底変換を往復すると情報が失われない。
    assert(conversion.field2nimber(conversion.nimber2field(a)) == a);
    // nim和はXORで、nim積は加法に対して分配的かつ結合的である。
    assert((a + b).x == (a.x ^ b.x));
    assert(a * (b + c) == a * b + a * c);
    assert((a * b) * c == a * (b * c));
    if (a.x) {
      // 2^bits個の元を持つ有限体の非零元は、2^bits-1乗で1になる。
      assert(a.pow(U(-1)) == N(1));
    }
  }
}

int main() {
  unsigned product[32][32]{};
  for (int a = 0; a < 32; ++a) {
    for (int b = 0; b < 32; ++b) {
      set<unsigned> excluded;
      for (int x = 0; x < a; ++x) {
        for (int y = 0; y < b; ++y) {
          excluded.insert(product[x][b] ^ product[a][y] ^ product[x][y]);
        }
      }
      while (excluded.count(product[a][b])) {
        ++product[a][b];
      }
      // Conwayのmexによる定義と、16/32/64bit全ての高速実装の積を照合する。
      assert((Nimber16(a) * Nimber16(b)).x == product[a][b]);
      assert((Nimber32(a) * Nimber32(b)).x == product[a][b]);
      assert((Nimber64(a) * Nimber64(b)).x == product[a][b]);
    }
  }
  check_field<Nimber16>();
  check_field<Nimber32>();
  check_field<Nimber64>();

  Nimber16 primitive = 10279;
  vector<int> first(65536, -1);
  Nimber16 value = 1;
  for (int exponent = 0; exponent < 65535; ++exponent) {
    first[value.x] = exponent;
    value *= primitive;
  }
  // 実際に全非零元を生成した根について、原始根判定も真になる。
  assert(count(first.begin(), first.end(), -1) == 1 && primitive.is_primitive_root());
  for (int x = 1; x < 65536; x += 137) {
    // 離散対数は、根を1回ずつ掛けて記録した最初の指数に一致する。
    assert(primitive.discrete_logarithm(Nimber16(x)) == first[x]);
  }
}
