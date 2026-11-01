// Verify: math/stern-brocot-tree.hpp
// Verify: math/stern-brocot-tree-binary-search.hpp
// Verify: math/enumerate-convex.hpp
// 分数の木を1段ずつのmediantで参照し、有理数探索は分子・分母、凸包は格子点を全列挙する。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "math/stern-brocot-tree.hpp"
#include "math/stern-brocot-tree-binary-search.hpp"
#include "math/enumerate-convex.hpp"

using Node = SternBrocotTreeNode<long long>;
using P = pair<long long, long long>;

P walk(const string& path) {
  P lower{0, 1};
  P upper{1, 0};
  for (char step : path) {
    P middle{lower.first + upper.first, lower.second + upper.second};
    if (step == 'L') {
      upper = middle;
    } else {
      lower = middle;
    }
  }
  return {lower.first + upper.first, lower.second + upper.second};
}

bool less_fraction(P a, P b) {
  return a.first * b.second < b.first * a.second;
}

int main() {
  mt19937 rng(732);
  for (int trial = 0; trial < 1000; ++trial) {
    string path(rng() % 15, 'L');
    for (auto& c : path) {
      c = rng() % 2 ? 'L' : 'R';
    }
    P value = walk(path);
    Node node(value.first * 3, value.second * 3);
    // 約分されていない入力から構築しても、1段ずつのmediantで得た分数と深さに一致する。
    assert(node.get() == value && node.depth() == (long long)path.size());
    Node reconstructed(node.seq);
    // 左移動を負数で表す圧縮経路からも、同じ分数を復元できる。
    assert(reconstructed == node);
    // 両境界のmediantが現在の値で、左境界・現在値・右境界の順に並ぶ。
    assert(less_fraction(node.lower_bound(), value) && less_fraction(value, node.upper_bound()));
    for (int removed = 0; removed <= (int)path.size(); ++removed) {
      auto ancestor = node;
      bool ok = ancestor.go_parent(removed);
      // まとめて親へ移動する操作を、経路の末尾を取り除いた木と比較する。
      assert(ok && ancestor.get() == walk(path.substr(0, path.size() - removed)));
    }
    string other(rng() % 15, 'L');
    for (auto& c : other) {
      c = rng() % 2 ? 'L' : 'R';
    }
    int common = 0;
    while (common < (int)min(path.size(), other.size()) && path[common] == other[common]) {
      ++common;
    }
    Node other_node(walk(other));
    // LCAは、1段ごとの経路の最長共通接頭辞を辿ったノードになる。
    assert(Node::lca(node, other_node).get() == walk(path.substr(0, common)));
  }

  for (long long limit = 0; limit <= 20; ++limit) {
    for (long long numerator = -1; numerator <= 25; ++numerator) {
      for (long long denominator = 1; denominator <= 7; ++denominator) {
        function<bool(P)> predicate = [&](P x) {
          return x.first * denominator >= numerator * x.second;
        };
        P lower{0, 1};
        P upper{1, 0};
        if (limit && numerator <= 0) {
          upper = lower;
        } else {
          for (long long q = 1; q <= limit; ++q) {
            for (long long p = 0; p <= limit; ++p) {
              if (gcd(p, q) != 1) {
                continue;
              }
              P value{p, q};
              if (predicate(value)) {
                if (less_fraction(value, upper)) {
                  upper = value;
                }
              } else if (less_fraction(lower, value)) {
                lower = value;
              }
            }
          }
        }
        auto got = binary_search_on_stern_brocot_tree<long long>(predicate, limit);
        // 制限内の全既約分数を試した両側の境界と比較し、0・無限大の番兵も確認する。
        assert(got == make_pair(lower, upper));
      }
    }
  }

  for (long long end = 0; end <= 25; ++end) {
    for (long long divisor = 1; divisor <= 8; ++divisor) {
      auto height = [&](long long x) { return (x * x + divisor - 1) / divisor; };
      function<bool(long long, long long)> inside = [&](long long x, long long y) {
        return 0 <= x && x <= end && y >= height(x);
      };
      function<long long(long long, long long, long long, long long)> candidate =
          [&](long long x, long long y, long long dx, long long dy) {
            if (dx == 0) {
              if (dy <= 0 || x < 0 || x > end) {
                return -1LL;
              }
              return max(1LL, (height(x) - y + dy - 1) / dy);
            }
            for (long long step = 1; x + dx * step <= end; ++step) {
              if (inside(x + dx * step, y + dy * step)) {
                return step;
              }
            }
            return -1LL;
          };
      vector<P> expected;
      for (long long x = 0; x <= end; ++x) {
        P c{x, height(x)};
        while (expected.size() >= 2) {
          P a = expected[expected.size() - 2];
          P b = expected.back();
          long long cross = (b.first - a.first) * (c.second - b.second) -
                            (b.second - a.second) * (c.first - b.first);
          if (cross > 0) {
            break;
          }
          expected.pop_back();
        }
        expected.push_back(c);
      }
      auto got = enumerate_convex<long long>(0, 0, end, inside, candidate);
      // 全ての下端格子点から単調鎖で求めた下側凸包と、頂点列を比較する。
      assert(got == expected);
    }
  }
}
