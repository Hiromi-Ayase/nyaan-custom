// Verify: game/surreal-number.hpp
// Verify: game/partisan-game.hpp
// 二進有理数を整数の共通分母で照合し、整数・分数の正準ゲーム木から値を再構成する。
#include <bits/stdc++.h>
using namespace std;
#include "game/surreal-number.hpp"
#include "game/partisan-game.hpp"

long long scaled(SurrealNumber a) {
  return a.p * (1LL << (12 - a.q));
}

int main() {
  using S = SurrealNumber;
  mt19937 rng(1101);
  for (int trial = 0; trial < 10000; ++trial) {
    S a((int)(rng() % 257) - 128, rng() % 7);
    S b((int)(rng() % 257) - 128, rng() % 7);
    long long x = scaled(a);
    long long y = scaled(b);
    // 2^12を共通分母とした整数計算で、加減算・比較・符号反転を確認する。
    assert(scaled(a + b) == x + y && scaled(a - b) == x - y && scaled(-a) == -x);
    assert((a < b) == (x < y) && (a == b) == (x == y) && (a >= b) == (x >= y));
    auto normal = S::normalize(a);
    assert(scaled(normal) == x && (normal.q == 0 || normal.p % 2 != 0));
    if (x > y) {
      swap(a, b);
      swap(x, y);
    }
    if (x == y) {
      continue;
    }
    auto middle = reduce(a, b);
    // 開区間内で最小の分母指数を選び、その中では絶対値が最小の分子を総当たりする。
    bool found = false;
    long long expected = 0;
    for (int q = 0; q <= 8 && !found; ++q) {
      for (int magnitude = 0; magnitude <= 20000 && !found; ++magnitude) {
        for (int sign : {1, -1}) {
          long long candidate = sign * magnitude * (1LL << (12 - q));
          if (x < candidate && candidate < y) {
            expected = candidate;
            found = true;
            break;
          }
        }
      }
    }
    assert(found && scaled(middle) == expected);
    // larger/smallerは0から片側へ整数をたどり、初めて境界を越える値になる。
    long long upper = 0;
    long long lower = 0;
    while (upper * 4096 <= x) {
      ++upper;
    }
    while (lower * 4096 >= x) {
      --lower;
    }
    assert(scaled(a.larger()) == upper * 4096 && scaled(a.smaller()) == lower * 4096);
  }
  using Board = pair<int, int>;
  auto normalize = [](Board b) {
    while (b.second > 0 && b.first % 2 == 0) {
      b.first /= 2;
      --b.second;
    }
    return b;
  };
  auto moves = [&](Board b) {
    b = normalize(b);
    vector<Board> left;
    vector<Board> right;
    auto [p, q] = b;
    if (q == 0) {
      if (p > 0) {
        left.emplace_back(p - 1, 0);
      }
      if (p < 0) {
        right.emplace_back(p + 1, 0);
      }
    } else {
      left.push_back(normalize({p - 1, q}));
      right.push_back(normalize({p + 1, q}));
    }
    return make_pair(left, right);
  };
  PartisanGameSolver<Board, decltype(moves)> solver(moves);
  for (int q = 0; q <= 6; ++q) {
    for (int p = -100; p <= 100; ++p) {
      // {整数の直前|}と{|直後}、分数の左右境界で作る正準ゲームは元のp/2^qを表す。
      assert(scaled(solver.get({p, q})) == p * (1LL << (12 - q)));
    }
  }
}
