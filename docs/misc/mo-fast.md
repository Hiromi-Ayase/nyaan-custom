## 処理順を調整した Mo 法

`Fast_Mo(n,q)` に `insert(l,r)` で半開区間をちょうど `q` 個登録する。`q >= 1` が必要。

`run(add_left,add_right,delete_left,delete_right,rem)` は空区間 `[0,0)` から端点を動かす。四つの更新関数は要素の添字を受け、`rem(query_id)` は現在の答えを保存する。呼び出し側の集計状態も空から始める。

未構築なら自動で `build()` する。ブロック順を局所改善して移動量を減らす。通常の移動回数の目安は $O(n\sqrt q+q)$、領域は $O(n+q)$。

#### 実装・検証

- [実装](../../misc/mo-fast.hpp)
- [Verify: mo-and-doubling.cpp](../../tests/unit/misc/mo-and-doubling.cpp)
