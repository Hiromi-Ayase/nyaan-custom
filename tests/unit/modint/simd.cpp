// Verify: modint/simd-montgomery.hpp
// Verify: modint/vectorize-modint.hpp
// Verify: math-fast/vectorize-modint.hpp
// SIMDの各レーンを独立した整数として扱い、加減乗算とMontgomery変換を通常の剰余演算と比較する。
// 全0・法-1・レーンごとに異なる値を含み、128bit版と256bit版の下位/上位積も確認する。
#include <bits/stdc++.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "modint/simd-montgomery.hpp"
#include "modint/vectorize-modint.hpp"
#include "math-fast/vectorize-modint.hpp"

int main() {
  using M = LazyMontgomeryModInt<998244353>;
  using V = vectorize_modint<M>;
  const unsigned mod = M::get_mod();
  mmint::set_mod<M>();
  mt19937 rng(2113);
  for (int trial = 0; trial < 10000; ++trial) {
    alignas(32) unsigned a[8];
    alignas(32) unsigned b[8];
    alignas(32) unsigned encoded_a[8];
    alignas(32) unsigned encoded_b[8];
    alignas(32) unsigned got[8];
    for (int i = 0; i < 8; ++i) {
      a[i] = trial == 0 ? 0 : trial == 1 ? mod - 1 : rng() % mod;
      b[i] = rng() % mod;
      encoded_a[i] = (unsigned long long)a[i] * (1ULL << 32) % mod;
      encoded_b[i] = (unsigned long long)b[i] * (1ULL << 32) % mod;
    }

    mmint x(_mm256_load_si256((__m256i*)a));
    mmint y(_mm256_load_si256((__m256i*)b));
    x = mmint::itom(x);
    y = mmint::itom(y);
    auto sum = mmint::mtoi(x + y);
    auto diff = mmint::mtoi(x - y);
    auto prod = mmint::mtoi(x * y);
    V vx = V::itom(V(_mm256_load_si256((__m256i*)a)));
    V vy = V::itom(V(_mm256_load_si256((__m256i*)b)));
    auto vs = V::mtoi(vx + vy);
    auto vd = V::mtoi(vx - vy);
    auto vp = V::mtoi(vx * vy);
    for (int i = 0; i < 8; ++i) {
      unsigned s = (a[i] + b[i]) % mod;
      unsigned d = (a[i] + mod - b[i]) % mod;
      unsigned p = (unsigned long long)a[i] * b[i] % mod;

      // mmintの各レーンの和が、通常の整数による和の剰余と一致する。
      assert(sum[i] == (int)s);

      // 差が負になる場合も、正規化した剰余として取得できる。
      assert(diff[i] == (int)d);

      // Montgomery表現から戻した積を、64bit整数の積の剰余と比較する。
      assert(prod[i] == (int)p);

      // テンプレート版の加算も、全8レーンで通常の剰余と一致する。
      assert(vs.at(i) == (int)s);

      // テンプレート版の減算も、負の差を正規化した剰余と一致する。
      assert(vd.at(i) == (int)d);

      // テンプレート版の乗算も、64bit整数の積の剰余と一致する。
      assert(vp.at(i) == (int)p);
    }

    // レーン単位の書き換えが隣のレーンに影響せず、最適化ありでも読み戻せることを調べる。
    for (int i = 0; i < 8; ++i) {
      sum[i] = a[i];
      vs.set(i, b[i]);
    }

    for (int i = 0; i < 8; ++i) {
      // 添字参照経由で書いた値を、同じレーンから正確に読み戻せる。
      assert(sum[i] == (int)a[i]);

      // set/at経由でも、書き込んだ値を正確に読み戻せる。
      assert(vs.at(i) == (int)b[i]);
    }

    __m256i ma = _mm256_load_si256((__m256i*)encoded_a);
    __m256i mb = _mm256_load_si256((__m256i*)encoded_b);
    auto result = montgomery_mul_256(ma, mb, _mm256_set1_epi32(M::r), _mm256_set1_epi32(mod));
    _mm256_store_si256((__m256i*)got, result);
    for (int i = 0; i < 8; ++i) {
      // 256bit版のMontgomery積を、通常の積に2^32を掛けて符号化した値と比較する。
      assert(got[i] % mod == (unsigned long long)a[i] * b[i] % mod * (1ULL << 32) % mod);
    }

    __m128i a128 = _mm_load_si128((__m128i*)encoded_a);
    __m128i b128 = _mm_load_si128((__m128i*)encoded_b);
    auto r128 = montgomery_mul_128(a128, b128, _mm_set1_epi32(M::r), _mm_set1_epi32(mod));
    _mm_store_si128((__m128i*)got, r128);
    for (int i = 0; i < 4; ++i) {
      // 128bit版でも、各レーンのMontgomery積が同じ符号化式に従う。
      assert(got[i] % mod == (unsigned long long)a[i] * b[i] % mod * (1ULL << 32) % mod);
    }

    _mm256_store_si256((__m256i*)got, my256_mulhi_epu32(ma, mb));
    for (int i = 0; i < 8; ++i) {
      // 各32bitレーンの上位積を、64bitで掛けて32bit右シフトした値と比較する。
      assert(got[i] == ((unsigned long long)encoded_a[i] * encoded_b[i] >> 32));
    }

    _mm256_store_si256((__m256i*)got, my256_mullo_epu32(ma, mb));
    for (int i = 0; i < 8; ++i) {
      // 256bit版の下位積を、64bitの積から下位32bitだけを取り出した値と比較する。
      assert(got[i] == (unsigned)((unsigned long long)encoded_a[i] * encoded_b[i]));
    }

    _mm_store_si128((__m128i*)got, my128_mulhi_epu32(a128, b128));
    for (int i = 0; i < 4; ++i) {
      // 128bit版の上位積も、64bitの積を32bit右シフトした値と比較する。
      assert(got[i] == ((unsigned long long)encoded_a[i] * encoded_b[i] >> 32));
    }

    _mm_store_si128((__m128i*)got, my128_mullo_epu32(a128, b128));
    for (int i = 0; i < 4; ++i) {
      // 128bit版の下位積も、各レーン独立に下位32bitが保存される。
      assert(got[i] == (unsigned)((unsigned long long)encoded_a[i] * encoded_b[i]));
    }
  }
}
