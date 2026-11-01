// Verify: segment-tree/li-chao-tree-abstruct.hpp
// 最小・最大の両方で、線分を全走査して点取得と区間内の最適評価点を照合する。
#include <bits/stdc++.h>
using namespace std;
#include "segment-tree/li-chao-tree-abstruct.hpp"

struct Line {
  long long a = 0;
  long long b = 0;

  long long operator()(long long x) const {
    return a * x + b;
  }
};

template <bool minimize>
void check() {
  constexpr long long inf = 1LL << 60;
  mt19937 rng(minimize ? 1206 : 1207);
  vector<long long> xs;
  for (int i = -30; i <= 30; ++i) {
    xs.push_back(i * i * i);
  }
  LiChaoTree<Line, minimize, true> tree(xs, Line{0, minimize ? inf : -inf});
  vector<array<long long, 4>> lines;
  for (int step = 0; step < 400; ++step) {
    long long a = (int)(rng() % 41) - 20;
    long long b = (int)(rng() % 101) - 50;
    int l = rng() % xs.size();
    int r = rng() % xs.size();
    if (l > r) {
      swap(l, r);
    }
    if (step % 3 == 0) {
      tree.add_line({a, b});
      l = 0;
      r = xs.size() - 1;
    } else {
      tree.add_segment(xs[l], xs[r] + 1, {a, b});
    }
    lines.push_back({a, b, xs[l], xs[r] + 1});
    vector<long long> expected(xs.size(), minimize ? inf : -inf);
    for (int i = 0; i < (int)xs.size(); ++i) {
      for (auto line : lines) {
        if (line[2] <= xs[i] && xs[i] < line[3]) {
          long long value = line[0] * xs[i] + line[1];
          expected[i] = minimize ? min(expected[i], value) : max(expected[i], value);
        }
      }
      auto [value, line] = tree.get_val(xs[i]);
      // 最適値と返された直線を実際に評価した値が、全走査の期待値に一致する。
      assert(value == expected[i] && line(xs[i]) == value);
    }
    for (int query = 0; query < 5; ++query) {
      l = rng() % xs.size();
      r = rng() % xs.size();
      if (l > r) {
        swap(l, r);
      }
      auto [x, value] = tree.get(xs[l], xs[r] + 1);
      long long answer = minimize ? *min_element(expected.begin() + l, expected.begin() + r + 1)
                                  : *max_element(expected.begin() + l, expected.begin() + r + 1);
      // 各直線は単調なので区間取得の前提を満たす。評価点が範囲内で、最適値を実現する。
      assert(xs[l] <= x && x <= xs[r] && value == answer);
      int index = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
      assert(xs[index] == x && expected[index] == answer);
    }
  }
}

int main() {
  check<true>();
  check<false>();
}
