// Verify: modulo/factorial.hpp
// Verify: modulo/multipoint-binomial-sum.hpp
// 階乗は1からの直接積、二項係数のprefix sumはPascal表を各クエリごとに足した値と比較する。
#include <bits/stdc++.h>
#include <immintrin.h>
using namespace std;
#include "modint/montgomery-modint.hpp"
#include "fps/ntt-friendly-fps.hpp"
#include "modulo/factorial.hpp"
#include "modulo/multipoint-binomial-sum.hpp"

int main() {
  using Mint = LazyMontgomeryModInt<998244353>;
  vector<long long> facts(1000001, 1);
  for (int n = 1; n < (int)facts.size(); ++n) {
    facts[n] = facts[n - 1] * n % 998244353;
  }
  vector<int> sizes{0,   1,   2,   3,   7,    15,   16,    17,    63,    64,     65,
                    255, 256, 257, 999, 1000, 1001, 65535, 65536, 65537, 1000000};
  for (int n : sizes) {
    // ブロック長の2冪境界と大きなnを、前から順に掛けただけの階乗表と比較する。
    assert(factorial<Mint>(n).get() == facts[n]);
  }
  vector<vector<long long>> pascal(201, vector<long long>(201));
  pascal[0][0] = 1;
  for (int n = 1; n <= 200; ++n) {
    pascal[n][0] = 1;
    for (int k = 1; k <= n; ++k) {
      pascal[n][k] = (pascal[n - 1][k - 1] + pascal[n - 1][k]) % 998244353;
    }
  }
  vector<pair<int, int>> queries;
  for (int n = 0; n <= 200; ++n) {
    queries.emplace_back(n, 0);
    queries.emplace_back(n, n);
    queries.emplace_back(n, n / 2);
  }
  mt19937 rng(1701);
  shuffle(queries.begin(), queries.end(), rng);
  auto actual = multipoint_binomial_sum<Mint>(queries);
  for (int i = 0; i < (int)queries.size(); ++i) {
    auto [n, k] = queries[i];
    long long sum = 0;
    for (int j = 0; j <= k; ++j) {
      sum = (sum + pascal[n][j]) % 998244353;
    }
    // Moで順序を変えて処理しても、各クエリは元の順序でC(n,0)..C(n,k)の和を返す。
    assert(actual[i].get() == sum);
  }
  // クエリが0件でも空配列を返す。
  assert(multipoint_binomial_sum<Mint>({}).empty());
}
