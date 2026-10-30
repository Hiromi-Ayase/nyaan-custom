## スライド窓の最小値・最大値

`SlideWindowMinimum(v,f,K)` は長さ `N+1` の配列を返し、`result[i]` に `[max(0,i-K),i)` の最良値を格納する。`result[0]` は 0。

`f(a,b)` は bool の比較ではなく、`min(a,b)` または `max(a,b)` のように選択した値を返す関数。`1 <= K <= N` とする。入力は非 const 参照だが変更しない。

単調 deque により時間 $O(N)$、返却配列を含む領域 $O(N)$。

#### 実装・検証

- [実装](../../data-structure/sliding-window-minimum.hpp)
- [検証: aoj-dsl-3-d.test.cpp](../../verify/verify-aoj-dsl/aoj-dsl-3-d.test.cpp)
