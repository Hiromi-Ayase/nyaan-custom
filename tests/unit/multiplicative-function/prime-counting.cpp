// Verify: multiplicative-function/prime-counting.hpp
// 単純なEratosthenesの篩で作った素数フラグを累積し、素数個数の期待値にする。
// 小さい全入力、平方数付近を含む100万以下の固定シード入力を比較する。
#include <bits/stdc++.h>
using namespace std;
#include "multiplicative-function/prime-counting.hpp"

int main() {
  const int max_n = 1000000;
  vector<int> composite(max_n + 1);
  vector<int> count(max_n + 1);
  for (int i = 2; i <= max_n; ++i) {
    if (!composite[i]) {
      for (long long j = 1LL * i * i; j <= max_n; j += i) {
        composite[j] = 1;
      }
    }

    count[i] = count[i - 1] + !composite[i];
  }

  for (int n = 0; n <= 3000; ++n) {
    // 小さいnを順に全て試し、エラトステネスの篩で作った素数個数の累積表と比較する。
    assert(prime_counting(n) == count[n]);
  }

  mt19937 rng(743);
  for (int q = 0; q < 200; ++q) {
    int n = 4 + rng() % (max_n - 3);

    // 大きさの異なるランダムなnでも、同じ篩の累積表と一致する。複数回呼出しも確認する。
    assert(prime_counting(n) == count[n]);
  }
}
