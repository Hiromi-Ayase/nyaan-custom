// Verify: math/sat-solver.hpp
// Verify: math/two-sat.hpp
// 小さい変数数で全真偽割当を試し、充足可能性と返された割当を照合する。単位節・含意も含む。
#include <bits/stdc++.h>
using namespace std;
#define NyaanLocal
#include "math/sat-solver.hpp"
#include "math/two-sat.hpp"

int main() {
  mt19937 rng(721);
  for (int n = 1; n <= 8; ++n) {
    for (int trial = 0; trial < 200; ++trial) {
      SatSolver general(n);
      two_sat binary;
      for (int i = 0; i < n; ++i) {
        // 動的な変数追加は、0から順に新しい添字を返す。
        assert(binary.add_var() == i);
      }
      vector<vector<pair<int, bool>>> clauses;
      vector<vector<pair<int, bool>>> binary_clauses;
      for (int step = 0; step < 20; ++step) {
        int length = 1 + rng() % min(n, 4);
        vector<int> variables(n);
        iota(variables.begin(), variables.end(), 0);
        shuffle(variables.begin(), variables.end(), rng);
        vector<pair<int, bool>> clause;
        for (int i = 0; i < length; ++i) {
          clause.emplace_back(variables[i], rng() % 2);
        }
        clauses.push_back(clause);
        if (length == 1) {
          general.set_val(clause[0].first, clause[0].second);
        } else if (length == 2 && step % 2) {
          general.if_then(clause[0].first, !clause[0].second, clause[1].first, clause[1].second);
        } else {
          general.add_clause(clause);
        }
        if (length <= 2) {
          binary_clauses.push_back(clause);
          int x = clause[0].second ? clause[0].first : ~clause[0].first;
          if (length == 1) {
            binary.set_val(x);
          } else {
            int y = clause[1].second ? clause[1].first : ~clause[1].first;
            if (step % 2) {
              binary.if_then(~x, y);
            } else {
              binary.add_clause(x, y);
            }
          }
        }
      }
      vector<int> limited;
      for (int i = 0; i < n; ++i) {
        if (rng() % 2) {
          limited.push_back(i);
        }
      }
      binary.at_most_one(limited);
      for (int i = 0; i < (int)limited.size(); ++i) {
        for (int j = 0; j < i; ++j) {
          binary_clauses.push_back({{limited[i], false}, {limited[j], false}});
        }
      }
      auto satisfies = [](const auto& formula, const vector<bool>& assignment) {
        for (const auto& clause : formula) {
          bool valid = false;
          for (auto [variable, value] : clause) {
            valid = valid || assignment[variable] == value;
          }
          if (!valid) {
            return false;
          }
        }
        return true;
      };
      bool expected_general = false;
      bool expected_binary = false;
      for (int mask = 0; mask < (1 << n); ++mask) {
        vector<bool> assignment(n);
        for (int i = 0; i < n; ++i) {
          assignment[i] = mask >> i & 1;
        }
        expected_general = expected_general || satisfies(clauses, assignment);
        expected_binary = expected_binary || satisfies(binary_clauses, assignment);
      }
      // 全真偽割当を試した結果と、一般CNFの充足可能性が一致する。
      assert(general.solve() == expected_general);
      if (expected_general) {
        // 真を返したときの割当は、登録した全ての節を実際に満たす。
        assert(satisfies(clauses, general.assigns));
      }
      // 補助変数を使うat_most_oneも含め、元の変数だけの全探索と2-SATが一致する。
      assert(binary.satisfiable() == expected_binary);
      if (expected_binary) {
        // 返された割当は、at_most_oneを2変数節へ展開した条件も全て満たす。
        assert(satisfies(binary_clauses, binary.answer()));
      }
    }
  }
}
