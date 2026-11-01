// Verify: misc/compress.hpp
// Verify: misc/interval-union.hpp
// Verify: misc/int_div.hpp
// Verify: misc/vector-pool.hpp
// Verify: misc/bitset-find-prev.hpp
// 座圧と区間和集合は集合、整数除算は有理数の大小、プールとビット探索は全走査を期待値にする。
#include <bits/stdc++.h>
using namespace std;
#include "misc/compress.hpp"
#include "misc/interval-union.hpp"
#include "misc/int_div.hpp"
#include "misc/vector-pool.hpp"
#include "misc/bitset-find-prev.hpp"

template <size_t N>
void check_bits() {
  mt19937 rng(1401 + N);
  Bitset<N> bits;
  vector<bool> expected(N);
  for (int step = 0; step < 1000; ++step) {
    int index = rng() % N;
    expected[index] = !expected[index];
    bits.flip(index);
    for (int i = 0; i <= (int)N; ++i) {
      int previous = i - 1;
      while (previous >= 0 && !expected[previous]) {
        --previous;
      }
      // 64ビット境界と全て0の語を跨いでも、i未満で最後に立つビットを返す。
      assert(bits._Find_prev(i) == previous);
      if (i == (int)N) {
        assert(bits._Find_last() == previous);
      }
    }
  }
}

int main() {
  mt19937 rng(1401);
  for (int trial = 0; trial < 1000; ++trial) {
    vector<int> values(rng() % 100);
    for (int& x : values) {
      x = (int)(rng() % 101) - 50;
    }
    set<int> sorted(values.begin(), values.end());
    compress<int> compressed(values);
    // 座圧の個数と逆引きは重複を除いた昇順集合に一致する。
    assert(compressed.size() == (int)sorted.size());
    int index = 0;
    for (int value : sorted) {
      assert(compressed[index++] == value);
    }
    for (int x = -60; x <= 60; ++x) {
      int smaller = count_if(sorted.begin(), sorted.end(), [&](int value) { return value < x; });
      assert(compressed.get(x) == smaller && compressed(x) == smaller);
    }
    vector<pair<int, int>> intervals;
    set<int> covered;
    for (int i = 0; i < trial % 30; ++i) {
      int l = (int)(rng() % 50) - 25;
      int r = l + 1 + rng() % 20;
      intervals.emplace_back(l, r);
      for (int x = l; x < r; ++x) {
        covered.insert(x);
      }
    }
    auto result = interval_union(intervals);
    set<int> actual;
    for (int i = 0; i < (int)result.size(); ++i) {
      auto [l, r] = result[i];
      // 出力区間は重複も隣接もせず、半開区間の整数点を全て保存する。
      if (i > 0) {
        assert(result[i - 1].second < l);
      }
      for (int x = l; x < r; ++x) {
        actual.insert(x);
      }
    }
    assert(actual == covered);
  }
  for (long long a = -100; a <= 100; ++a) {
    for (long long b = -20; b <= 20; ++b) {
      if (b == 0) {
        continue;
      }
      long long numerator = b > 0 ? a : -a;
      long long denominator = abs(b);
      long long fl = floor(a, b);
      long long ce = ceil(a, b);
      long long un = under(a, b);
      long long ov = over(a, b);
      // 除算の実装を再利用せず、整数を掛け戻した不等式で4種類の丸めを確認する。
      assert(fl * denominator <= numerator && numerator < (fl + 1) * denominator);
      assert((ce - 1) * denominator < numerator && numerator <= ce * denominator);
      assert(un * denominator < numerator && numerator <= (un + 1) * denominator);
      assert((ov - 1) * denominator <= numerator && numerator < ov * denominator);
      if (b > 0) {
        long long m = modulo(a, b);
        assert(0 <= m && m < b && (a - m) % b == 0);
      }
    }
  }
  VectorPool<string> pool(1);
  map<int, string> active;
  for (int step = 0; step < 2000; ++step) {
    if (!active.empty() && rng() % 3 == 0) {
      auto it = active.begin();
      advance(it, rng() % active.size());
      pool.free(it->first);
      active.erase(it);
    } else {
      string value = to_string(step);
      int pointer = pool.my_new(value);
      // 0はnilで、再利用した番号も現在生存する別要素と重ならない。
      assert(pointer != 0 && !active.count(pointer));
      active[pointer] = value;
    }
    for (auto [pointer, value] : active) {
      assert(pool[pointer] == value);
    }
  }
  pool.clear();
  // clear後は最初の利用可能番号1へ戻り、my_newは古い値を初期化し直す。
  int first = pool.my_new("reset");
  assert(first == 1 && pool[first] == "reset");
  check_bits<1>();
  check_bits<63>();
  check_bits<64>();
  check_bits<65>();
  check_bits<129>();
  check_bits<257>();
}
