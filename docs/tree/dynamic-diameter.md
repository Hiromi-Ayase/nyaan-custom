## 辺重み更新付きの木の直径

`DynamicDiameter<T>(g)` は固定された重み付き木を Static Top Tree で管理する。非空・連結な木と、非負の辺重みを用いる。

`update(u,v,x)` は存在する辺 u-v の重みを x へ変更する。`get()` は `(直径の長さ, (端点u,端点v))`。木の形を変える link/cut 操作はない。更新は内部の重みへ反映され、入力グラフを書き換えない。

構築は保守的に $O(n\log n)$、更新 $O(\log n)$、取得 $O(1)$、領域 $O(n)$。

#### 実装・検証

- [実装](../../tree/dynamic-diameter.hpp)
- [Verify: dynamic-diameter.cpp](../../tests/unit/tree/dynamic-diameter.cpp)
