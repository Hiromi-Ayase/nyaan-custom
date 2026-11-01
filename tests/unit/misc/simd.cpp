// Verify: misc/simd.hpp
// 8レーンの演算をスカラーの整数計算と比較する。マクロ自体はAVX2だけを使用する。
#include <bits/stdc++.h>
#include <immintrin.h>
using namespace std;
#pragma GCC push_options
#include "misc/simd.hpp"
#pragma GCC pop_options

__attribute__((target("avx2"))) void check() {
  mt19937 rng(1405);
  for (int trial = 0; trial < 1000; ++trial) {
    ALIGN int a[8];
    ALIGN int b[8];
    ALIGN int result[8];
    for (int i = 0; i < 8; ++i) {
      a[i] = rng() % 1000;
      b[i] = rng() % 1000;
    }
    m256 x = LOAD(a);
    m256 y = LOAD(b);
    STORE(result, ADD(x, y));
    // 32ビットレーンごとの加減算は、隣のレーンへ影響しない。
    for (int i = 0; i < 8; ++i) {
      assert(result[i] == a[i] + b[i]);
    }
    STORE(result, SUB(x, y));
    for (int i = 0; i < 8; ++i) {
      assert(result[i] == a[i] - b[i]);
    }
    STORE(result, AND(x, y));
    // ビット演算と比較マスクを通常の整数演算で照合する。
    for (int i = 0; i < 8; ++i) {
      assert(result[i] == (a[i] & b[i]));
    }
    STORE(result, OR(x, y));
    for (int i = 0; i < 8; ++i) {
      assert(result[i] == (a[i] | b[i]));
    }
    STORE(result, XOR(x, y));
    for (int i = 0; i < 8; ++i) {
      assert(result[i] == (a[i] ^ b[i]));
    }
    STORE(result, CMP(x, y));
    for (int i = 0; i < 8; ++i) {
      assert(result[i] == (a[i] > b[i] ? -1 : 0));
    }
    STORE(result, MADD(x, y, SET(1000)));
    // 剰余マクロは0を法そのものでも表せる冗長表現。値域と合同の両方を確認する。
    for (int i = 0; i < 8; ++i) {
      assert(0 <= result[i] && result[i] <= 1000);
      assert(result[i] % 1000 == (a[i] + b[i]) % 1000);
    }
    STORE(result, MSUB(x, y, SET(1000)));
    for (int i = 0; i < 8; ++i) {
      assert(0 <= result[i] && result[i] <= 1000);
      assert(result[i] % 1000 == (a[i] - b[i] + 1000) % 1000);
    }
    STORE(result, SETLO(x));
    // 64ビットごとの下位/上位32ビットを複製する並べ替えを確認する。
    for (int i = 0; i < 8; ++i) {
      assert(result[i] == a[i / 2 * 2]);
    }
    STORE(result, SETHI(x));
    for (int i = 0; i < 8; ++i) {
      assert(result[i] == a[i / 2 * 2 + 1]);
    }
    ALIGN unsigned long long wide[4];
    STORE(wide, ADD64(CAST64(x), SET64(1ULL << 32)));
    // 64ビット加算は下位32ビットを保持し、上位側へ指定値を足す。
    for (int i = 0; i < 4; ++i) {
      assert(wide[i] == (1ULL << 32) + a[2 * i]);
    }
  }
}

int main() {
  check();
}
