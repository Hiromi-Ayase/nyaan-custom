## 有理数上の二分探索

`binary_search_on_stern_brocot_tree<I>(f,INF)` は分子・分母が INF 以下の非負既約分数から、f が偽となる最大値と真となる最小値を返す。f は分数値に対して偽→真へ単調な述語で、引数は `(分子,分母)`。

`f(0/1)` が真なら両方 0/1、真になる値がなければ上限は 1/0。INF=0 は `(0/1,1/0)`。INF>=0 とし、探索中の積や倍増にも I の余裕を持たせる。

Stern–Brocot 木の連続した同方向移動を倍増・二分探索でまとめる。時間は経路長と f の計算量に依存する。

#### 実装・検証

- [実装](../../math/stern-brocot-tree-binary-search.hpp)
- [Verify: stern-brocot.cpp](../../tests/unit/math/stern-brocot.cpp)
