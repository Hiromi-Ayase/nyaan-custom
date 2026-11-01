// Verify: data-structure/slide-window-aggregation.hpp
// Verify: data-structure/slide-window-aggregation-deque.hpp
// 非可換な文字列連結を演算に使い、dequeを左から連結した結果と比較する。
// 空状態・一要素・片側に偏った操作・両端の追加削除を混ぜ、転送時の順序も検証する。
#include <bits/stdc++.h>
using namespace std;
#include "data-structure/slide-window-aggregation.hpp"
#include "data-structure/slide-window-aggregation-deque.hpp"

int main() {
  mt19937 rng(541);
  auto concat = [](string a, string b) { return a + b; };
  SlideWindowAggregation<string, decltype(concat)> queue(concat, "");
  SlideWindowAggregationDeque<string, decltype(concat)> both(concat, "");
  deque<string> a;
  deque<string> b;
  for (int step = 0; step < 10000; ++step) {
    string x(1, 'a' + rng() % 26);
    if (a.empty() || rng() % 2) {
      queue.push(x);
      a.push_back(x);
    } else {
      queue.pop();
      a.pop_front();
    }

    int op = rng() % 4;
    if (b.empty() || op == 0) {
      both.push_front(x);
      b.push_front(x);
    } else if (op == 1) {
      both.push_back(x);
      b.push_back(x);
    } else if (op == 2) {
      both.pop_front();
      b.pop_front();
    } else {
      both.pop_back();
      b.pop_back();
    }

    string qa;
    string qb;
    for (auto& s : a) {
      qa += s;
    }

    for (auto& s : b) {
      qb += s;
    }

    // 現在の要素を左から連結した文字列と比較し、非可換な演算でも順序が保たれることを確認する。
    assert(queue.query() == qa && both.query() == qb);
    if (!b.empty()) {
      // 両端で挿入・削除した後の先頭・末尾が、参照用dequeと一致する。
      assert(both.front() == b.front() && both.back() == b.back());
    }
  }
}
