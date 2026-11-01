## 使用頻度の高いセグメント木

一点代入と区間集約の組を、それぞれ独立した struct にまとめる。各 struct が `S`, `op`, `e` と、対応する `atcoder::segtree` の別名 `Tree` を持つ。木の処理は同梱の AtCoder Library を使う。

| struct | 操作 | 集約値 `S` | 単位元 |
| --- | --- | --- | --- |
| `SegmentTree_RangeMax<T,MINF>` | 一点代入・区間最大値 | `T` | `MINF` |
| `SegmentTree_RangeMin<T,INF>` | 一点代入・区間最小値 | `T` | `INF` |
| `SegmentTree_RangeSum<T>` | 一点代入・区間和 | `T` | `T{}`（零） |

`MINF` / `INF` は、実際に扱う値の下限・上限を覆う値を指定する。和の途中値は `T` に収める。

#### 使用例

```cpp
#include "segment-tree/segment-tree-utility.hpp"
#include <limits>
#include <vector>

void example() {
  using Minimum = SegmentTree_RangeMin<long long,
      std::numeric_limits<long long>::max()>;
  Minimum::Tree minimum(std::vector<long long>{1, 2, 3});
  minimum.set(0, 10);
  auto value = minimum.prod(0, 3);  // 2

  using Sum = SegmentTree_RangeSum<long long>;
  Sum::Tree sums(std::vector<long long>{1, 2, 3});
  sums.set(1, sums.get(1) + 5);
  auto total = sums.prod(0, 3);  // 11
}
```

#### 共通 API

- `Tree(n)` は単位元を `n` 個並べた列、`Tree(v)` は配列から構築する。デフォルト構築は空の列。
- `set(p,x)` は一点代入、`get(p)` は一点取得。一点加算は `set(p,get(p)+x)`。
- `prod(l,r)` は半開区間 `[l,r)` の集約値。空区間は `e()`。
- `all_prod()` は列全体の集約値。
- `max_right(l,check)` / `min_left(r,check)` は ACL の境界探索。`check(e())` が真で、区間を伸ばすと真から偽へ一度だけ変わる条件を指定する。

構築・領域は $O(n)$、`set`, `prod`, 境界探索は $O(\log n)$、`get`, `all_prod` は $O(1)$。

独自の集約は `atcoder/segtree.hpp` を読み込み、`atcoder::segtree<S,op,e>` を直接使う。

#### 実装・検証

- [実装](../../segment-tree/segment-tree-utility.hpp)
- [AtCoder Library の実装](../../atcoder/segtree.hpp)
- [Verify: utilities.cpp](../../tests/unit/segment-tree/utilities.cpp)
