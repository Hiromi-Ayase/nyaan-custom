## 内部用の乱数シード

`internal::seed()` は `NyaanLocal` 定義かつ `RANDOMIZED_SEED` 未定義なら固定値、それ以外は時刻を混ぜた 64 bit 値を返す。

`deterministic_seed()` / `non_deterministic_seed()` を明示的に選ぶこともできる。状態を更新する乱数生成器ではなく、連続呼び出しで同値になる可能性がある。時間・追加領域 $O(1)$。

#### 実装・検証

- [実装](../../internal/internal-seed.hpp)
- [Verify: hash.cpp](../../tests/unit/internal/hash.cpp)
