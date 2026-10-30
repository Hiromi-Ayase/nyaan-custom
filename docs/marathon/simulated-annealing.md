#### テンプレート

```
using score_t = double;
struct Input {
  Input() = default;
  void scan() {}
};
struct State {
  struct Diff {
    const State *st;
    Diff() = default;
    Diff(const State &state) : st(&state) {}
    double diff() const {}
  };

  State() = default;
  State(const Input &input) {}
  void update(const Diff &b) {}
  void undo(const Diff &) {}
  score_t score() const {}
  bool operator>(const State &s) { return score() > s.score(); };
  void dump() {}
};
using SA = Simulated_Annealing<Input, State, typename State::Diff>;
```

#### 実装・検証

- [実装](../../marathon/simulated-annealing.hpp)
- [検証: simulated-annealing.test.cpp](../../verify/verify-unit-test/simulated-annealing.test.cpp)
