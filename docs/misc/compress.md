## 座標圧縮

`compress<T>(v)` は値をソート・重複除去して `xs` に保持する。`get(x)` / `operator()(x)` は `x` 以上の最初の値の添字、`operator[](i)` は元の値、`size()` は異なる値の個数。

未登録値への `get` も lower_bound として動作し、存在判定にはならない。構築 $O(n\log n)$、検索 $O(\log n)$、領域 $O(n)$。

#### 実装・検証

- [実装](../../misc/compress.hpp)
- [Verify: basic-utilities.cpp](../../tests/unit/misc/basic-utilities.cpp)
