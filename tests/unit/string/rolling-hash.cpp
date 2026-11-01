// Verify: string/rolling-hash.hpp
// 基数を固定し、128bit整数による愚直な多項式評価を期待値とする。
// 空区間・全区間・連結・文字列検索・LCP・辞書順比較を確認する。
#include <bits/stdc++.h>
using namespace std;
#include "string/rolling-hash.hpp"

int main() {
  mt19937 rng(731);
  // Fix the polynomial base too, so a failing hash comparison is reproducible.
  roriha::basis = roriha::Hash::set(1000003);
  for (int n : {0, 1, 2, 17, 65}) {
    for (int trial = 0; trial < 30; ++trial) {
      string s(n, 'a');
      for (char& c : s) {
        c += rng() % 4;
      }

      roriha hash(s);

      // 元の文字列長を保持している。空文字列では長さ0になる。
      assert(hash.size() == n);
      for (int l = 0; l <= n; ++l) {
        for (int r = l; r <= n; ++r) {
          string sub = s.substr(l, r - l);
          // Independent polynomial evaluation in integers modulo 2^61-1.
          unsigned long long expected = 0;
          unsigned long long mod = (1ULL << 61) - 1;
          for (unsigned char c : sub) {
            expected = ((__uint128_t)expected * 1000003 + c) % mod;
          }

          // 区間の各文字から128bit整数で計算した多項式ハッシュと一致する。
          assert(hash.get(l, r) == roriha::Hash::set(expected));

          // 切り出した文字列の一括ハッシュも、同じ多項式の値になる。
          assert(roriha::get_hash(sub) == roriha::Hash::set(expected));
          int m = l + (r - l) / 2;

          // 途中で分割した2区間のハッシュを結合すると、分割前の値に戻る。
          assert(roriha::unite(hash.get(l, m), hash.get(m, r), r - m) == hash.get(l, r));

          // 部分文字列の最初の出現位置が、std::string::findと一致する。
          assert(hash.find(sub) == (int)s.find(sub));
        }
      }

      for (int a = 0; a <= n; ++a) {
        for (int b = 0; b <= n; ++b) {
          int common = 0;
          while (max(a, b) + common < n && s[a + common] == s[b + common]) {
            ++common;
          }

          // 接尾辞を1文字ずつ比べた共通接頭辞長と一致する。
          assert(roriha::lcp(hash, hash, a, b) == common);
          string x = s.substr(a);
          string y = s.substr(b);

          // ハッシュを使った辞書順判定が、実際の接尾辞の比較結果と一致する。
          assert(roriha::strcmp(hash, hash, a, b) == (x > y) - (x < y));
        }
      }
    }
  }
}
