// Verify: misc/base64.hpp
// 独自形式の先頭ビット幅と6ビット詰めをビット列から作り、符号化結果と復号を両方検証する。
#include <bits/stdc++.h>
using namespace std;
#include "misc/base64.hpp"

int main() {
  const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/.";
  mt19937_64 rng(1404);
  for (int width = 6; width <= 63; ++width) {
    for (int n = 1; n <= 25; ++n) {
      vector<long long> values(n);
      unsigned long long mask = (1ULL << width) - 1;
      for (auto& x : values) {
        x = rng() & mask;
      }
      values[0] = 1LL << (width - 1);
      vector<int> bits;
      for (auto x : values) {
        for (int i = 0; i < width; ++i) {
          bits.push_back((x >> i) & 1);
        }
      }
      string expected(1, alphabet[width]);
      for (int i = 0; i < (int)bits.size(); i += 6) {
        int chunk = 0;
        for (int j = 0; j < 6 && i + j < (int)bits.size(); ++j) {
          chunk += bits[i + j] * (1 << j);
        }
        expected += alphabet[chunk];
      }
      // 標準Base64ではない独自の並びを、1ビットずつ構築した文字列と比較する。
      assert(Base64::encode(values) == expected);
      // 最後の6ビット単位に端数がある場合も、元の要素数と値へ復元できる。
      assert(Base64::decode(expected) == values);
    }
  }
}
