// Verify: game/impartial-game.hpp
// 石取りのmex表と分割ゲームの直積を直接計算し、取得した勝ち手がGrundy数0へ遷移するか調べる。
#include <bits/stdc++.h>
using namespace std;
#include "game/impartial-game.hpp"

int main() {
  vector<int> expected(100);
  for (int n = 1; n < 100; ++n) {
    set<int> next;
    for (int take : {1, 3, 4}) {
      if (n >= take) {
        next.insert(expected[n - take]);
      }
    }
    while (next.count(expected[n])) {
      ++expected[n];
    }
  }
  auto moves = [](int n) {
    vector<pair<int, int>> result;
    for (int take : {1, 3, 4}) {
      if (n >= take) {
        result.emplace_back(n - take, take);
      }
    }
    return result;
  };
  ImpartialGameSolver<int, int> solver(moves);
  ImpartialGameSolver<int> simple;
  simple.set_func([](int n) {
    vector<int> result;
    for (int take : {1, 3, 4}) {
      if (n >= take) {
        result.push_back(n - take);
      }
    }
    return result;
  });
  for (int n = 0; n < 100; ++n) {
    // 終端を0として順に作ったmex表と、再帰メモ化の値が一致する。
    assert(solver.get(n) == expected[n] && simple.get(n) == expected[n]);
    if (expected[n]) {
      int take = solver.get_best_move(n);
      // 返された手が合法で、相手にGrundy数0の局面を渡す。
      assert((take == 1 || take == 3 || take == 4) && take <= n && expected[n - take] == 0);
    }
  }
  for (int a = 0; a < 20; ++a) {
    for (int b = 0; b < 20; ++b) {
      vector<int> piles{a, b};
      // 複数局面の和は個別Grundy数のXORになる。
      assert(solver.get(piles) == (expected[a] ^ expected[b]));
      if (solver.get(piles)) {
        auto [index, take] = solver.get_best_move(piles);
        assert(0 <= index && index < 2 && take <= piles[index] &&
               (take == 1 || take == 3 || take == 4));
        piles[index] -= take;
        // どちらの山を選んだ場合でも、実際に適用すると負け局面になる。
        assert((expected[piles[0]] ^ expected[piles[1]]) == 0);
      }
    }
  }
  auto split = [](int n) {
    vector<pair<vector<int>, int>> result;
    for (int left = 0; left < n; ++left) {
      result.push_back({{left, n - 1 - left}, left});
    }
    return result;
  };
  ImpartialGameSolver<int, int, true> splitting(split);
  vector<int> grundy(50);
  for (int n = 1; n < 50; ++n) {
    set<int> next;
    for (int left = 0; left < n; ++left) {
      next.insert(grundy[left] ^ grundy[n - 1 - left]);
    }
    while (next.count(grundy[n])) {
      ++grundy[n];
    }
    // 1石を取り除いて左右の2ゲームへ分割する場合も、全ての分割のmexと一致する。
    assert(splitting.get(n) == grundy[n]);
    if (grundy[n]) {
      int left = splitting.get_best_move(n);
      assert(0 <= left && left < n && (grundy[left] ^ grundy[n - 1 - left]) == 0);
    }
  }
}
