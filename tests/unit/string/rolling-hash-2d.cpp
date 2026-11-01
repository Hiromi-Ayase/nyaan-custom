// Verify: string/rolling-hash-2d.hpp
// 縦横の基数を固定し、各矩形を二重ループで多項式評価して比較する。
// 空行列、幅0、一行、一列、全体・部分矩形と、縦横サイズを変えた再構築を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "string/rolling-hash-2d.hpp"

int main() {
  using RH = RollingHash2D<string, 1>;
  RH::basis[0] = RH::Hash::set(1009);
  RH::basis[1] = RH::Hash::set(1013);
  RH hash;
  // デフォルト構築は空行列を表し、空矩形のハッシュは0になる。
  assert(hash.get(0, 0, 0, 0) == RH::Hash::set(0));
  mt19937 rng(9931);
  for (int h = 1; h <= 9; ++h) {
    for (int w = 0; w <= 9; ++w) {
      vector<string> a(h, string(w, 'a'));
      for (auto& row : a) {
        for (char& c : row) {
          c += rng() % 4;
        }
      }

      // 同じインスタンスを再利用し、幅の増加・縮小でも全行が再確保されるか調べる。
      hash.build(a);
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
  hash.build({"a"});
  hash.build({"ab"});
  // 1行のまま幅を増やしても、直接評価した1009/1013進ハッシュになる。
  assert(hash.get(0, 0, 1, 2) == RH::Hash::set('a' * 1013ULL + 'b'));
  hash.build({});
  // 非空から空への再構築でも、過去の寸法や係数を残さない。
  assert(hash.h == 0 && hash.w == 0 && hash.get(0, 0, 0, 0) == RH::Hash::set(0));
}
