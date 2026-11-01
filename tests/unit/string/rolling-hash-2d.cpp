// Verify: string/rolling-hash-2d.hpp
// 縦横の基数を固定し、各矩形を二重ループで多項式評価して比較する。
// 幅0、一行、一列、全体および部分矩形を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "string/rolling-hash-2d.hpp"

int main() {
  using RH = RollingHash2D<string, 1>;
  RH::basis[0] = RH::Hash::set(1009);
  RH::basis[1] = RH::Hash::set(1013);
  mt19937 rng(9931);
  for (int h = 1; h <= 9; ++h) {
    for (int w = 0; w <= 9; ++w) {
      vector<string> a(h, string(w, 'a'));
      for (auto& row : a) {
        for (char& c : row) {
          c += rng() % 4;
        }
      }

      RH hash(a);
      for (int u = 0; u < h; ++u) {
        for (int d = u + 1; d <= h; ++d) {
          for (int l = 0; l <= w; ++l) {
            for (int r = l; r <= w; ++r) {
              vector<string> sub;
              unsigned long long expected = 0;
              unsigned long long mod = (1ULL << 61) - 1;
              for (int y = u; y < d; ++y) {
                sub.push_back(a[y].substr(l, r - l));
                unsigned long long row = 0;
                for (int x = l; x < r; ++x) {
                  row = ((__uint128_t)row * 1013 + a[y][x]) % mod;
                }

                expected = ((__uint128_t)expected * 1009 + row) % mod;
              }

              // 長方形内を二重ループで積算した多項式ハッシュと、区間取得の結果を比較する。
              assert(hash.get(u, l, d, r) == RH::Hash::set(expected));

              // 切り出した二次元配列の一括ハッシュも、同じ多項式の値になる。
              assert(RH::get_hash(sub) == RH::Hash::set(expected));
            }
          }
        }
      }
    }
  }
}
