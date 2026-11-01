// Verify: marathon/simulated-annealing.hpp
// Verify: marathon/sa-manager.hpp
// 温度0で改善だけを採用すること、棄却時の巻き戻し、複数状態のスコア整合性と終了を検証する。
#include <bits/stdc++.h>
using namespace std;
#include "marathon/simulated-annealing.hpp"
#include "marathon/sa-manager.hpp"

struct Input {
  Timer* timer = nullptr;
};
struct Diff;

struct State {
  Timer* timer = nullptr;
  int value = 0;
  int attempts = 0;
  int accepted = 0;
  int rejected = 0;
  State() = default;

  State(const Input& input) : timer(input.timer) {}

  int score() const {
    return value;
  }

  void dump() {}

  void update(const Diff&);
  void undo(const Diff&);
};

struct Diff {
  int old;
  int delta;

  Diff(State& state) : old(state.value), delta(state.attempts % 2 == 0 ? 1 : -1) {
    ++state.attempts;
    state.value += delta;
    // 256回でタイマーを進め、時間待ちをせず外側ループの終了条件を成立させる。
    if (state.attempts == 256) {
      state.timer->st -= chrono::seconds(10);
    }
  }

  int diff() const {
    return delta;
  }
};

void State::update(const Diff& d) {
  assert(d.delta > 0);
  ++accepted;
}

void State::undo(const Diff& d) {
  assert(d.delta < 0);
  value = d.old;
  ++rejected;
}

int initial_count = 0;
int update_count = 0;

pair<int, int> initial_state() {
  int value = ++initial_count;
  return {value, value};
}

void improve(int& state, int& score, double threshold) {
  // SA_managerが渡す閾値は有限の非正値で、状態とスコアを同期して更新できる。
  assert(isfinite(threshold) && threshold <= 0 && state == score);
  state = min(100, state + 1);
  score = state;
  ++update_count;
}

int main() {
  Timer timer;
  Simulated_Annealing<Input, State, Diff> solver(5000, 0, 0, &timer);
  auto result = solver.run(Input{&timer});
  // 改善128回だけが残り、悪化128回はundoで正確に取り消される。
  assert(result.attempts == 256 && result.accepted == 128 && result.rejected == 128 &&
         result.score() == 128);
  solver.reset();
  assert(timer.elapsed() < 5000);
  for (int size : {1, 5}) {
    Timer clock;
    initial_count = 0;
    update_count = 0;
    SA_manager<int, int> manager(clock, 1, 0, 10, size);
    auto best = manager.run<initial_state, improve>();
    // 実行回数は壁時計に依存するので固定せず、全ての状態でスコアの整合性と値域を確認する。
    assert(initial_count == size && best.first == best.second && size <= best.second &&
           best.second <= 100);
    for (auto [state, score] : manager.states) {
      assert(state == score && score <= best.second);
    }
  }
  Timer expired;
  expired.st -= chrono::seconds(1);
  initial_count = 0;
  update_count = 0;
  SA_manager<int, int> stopped(expired, 1, 0, 1, 5);
  auto best = stopped.run<initial_state, improve>();
  // 開始時点で制限時間を過ぎていれば更新を呼ばず、最良の初期状態を返す。
  assert(update_count == 0 && best == make_pair(5, 5));
}
