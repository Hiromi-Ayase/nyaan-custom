## 多腕バンディットによる選択

`MultiArmedBandit(n)` は n 個の選択肢から報酬最大化を狙うヒューリスティック。`n > 0` とする。

`play()` が選んだ番号に対して、必ず一度 `reward(y)` を呼んでから次の `play()` を行う。最初は各選択肢を試し、その後は平均報酬の指数に基づいて選ぶ。`best()` は現在の最大重みの選択肢。

通常の選択は $O(n)$、領域 $O(n)$。温度が 0 になる、指数がオーバーフローするなど報酬の尺度に依存するため、報酬設計と値域を確認して使う。理論的な最適性を保証する実装ではない。

#### 実装・検証

- [実装](../../marathon/multi-armed-bandit.hpp)
- [Verify: top-k-and-bandit.cpp](../../tests/unit/marathon/top-k-and-bandit.cpp)
