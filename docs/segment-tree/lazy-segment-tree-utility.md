## 使用頻度の高い遅延セグメント木

6 種類の区間操作を、それぞれ独立した struct にまとめる。各 struct が `S`, `F`, `op`, `e`, `mapping`, `composition`, `id` と、対応する `atcoder::lazy_segtree` の別名 `Tree` を持つ。木の処理は同梱の AtCoder Library を使う。

| struct | 区間操作 | 集約値 `S` | 操作 `F` |
| --- | --- | --- | --- |
| `SegmentTree_RangeAdd_RangeMax<T,MINF>` | 加算・最大値 | `T` | `T` |
| `SegmentTree_RangeAdd_RangeMin<T,INF>` | 加算・最小値 | `T` | `T` |
| `SegmentTree_RangeAdd_RangeSum<T>` | 加算・和 | `{T sum; int length;}` | `T` |
| `SegmentTree_RangeUpdate_RangeMax<T,MINF>` | 代入・最大値 | `T` | `std::optional<T>` |
| `SegmentTree_RangeUpdate_RangeMin<T,INF>` | 代入・最小値 | `T` | `std::optional<T>` |
| `SegmentTree_RangeUpdate_RangeSum<T>` | 代入・和 | `{T sum; int length;}` | `std::optional<T>` |

`MINF` / `INF` は集約の単位元で、実際に扱う値の下限・上限を覆う値を指定する。加算の途中値は `T` に収める。和の `S` は `sum` に区間和、`length` に区間長を保持する。

#### 使用例

```cpp
#include "segment-tree/lazy-segment-tree-utility.hpp"
#include <limits>
#include <vector>

void example() {
  using Spec = SegmentTree_RangeUpdate_RangeMin<long long,
      std::numeric_limits<long long>::max()>;
  Spec::Tree seg(std::vector<long long>{1, 2, 3});
  seg.apply(0, 2, 10LL);
  auto minimum = seg.prod(0, 3);  // 3
  seg.apply(0, 3, Spec::id());    // 何もしない

  using Sum = SegmentTree_RangeAdd_RangeSum<long long>;
  Sum::Tree sums(std::vector<Sum::S>{{1, 1}, {2, 1}, {3, 1}});
  sums.apply(0, 3, 2LL);
  auto total = sums.prod(0, 3).sum;  // 12
}
```

和の初期値は各要素を `{value, 1}` にする。零の列なら `std::vector<Sum::S>(n, {0, 1})` を渡す。`Tree(n)` は `e()` の列を作るため、和の木では各要素の長さも `0` になる。

#### 共通 API

- `apply(l,r,action)` は半開区間 `[l,r)` へ操作を適用し、`apply(p,action)` は一点への適用。
- `prod(l,r)` / `all_prod()` は区間全体・列全体の集約値。
- `set(p,value)` / `get(p)` は一点の代入・取得。和の一点代入は `set(p,{value,1})`。
- `max_right` / `min_left` は ACL の境界探索。述語は集約型 `S` を受け取り、単位元で真になる単調な条件とする。

`mapping(action,value)` は操作が先。`composition(newer,older)` は **古い操作の後に新しい操作**を適用する合成。代入の単位元は `std::nullopt` であり、`0`, `INF`, `MINF` なども実際の値として代入できる。

構築・領域は $O(n)$、更新・区間取得・境界探索は $O(\log n)$、`all_prod()` は $O(1)$。

独自の操作は `atcoder/lazysegtree.hpp` を読み込み、`atcoder::lazy_segtree<S,op,e,F,mapping,composition,id>` を直接使う。

#### 実装・検証

- [実装](../../segment-tree/lazy-segment-tree-utility.hpp)
- [AtCoder Library の実装](../../atcoder/lazysegtree.hpp)
- [Verify: utilities.cpp](../../tests/unit/segment-tree/utilities.cpp)
