## 復元付き XOR 線形基底

`Sweep<T>` に `add(x,id)` でベクトルと ID を登録する。配列からの構築では添字が ID になる。

`restore(x)` は `(生成できるか, 使用する ID の昇順列)`。成功時は列の要素の XOR が x。0 は空集合で復元できる。ID は元要素を区別できるよう一意にする。

各基底に ID 集合を保持し、消去のたびに対称差を取る。時間・領域はビット幅だけでなく復元集合の大きさにも依存する。

#### 実装・検証

- [実装](../../math/sweep-restore.hpp)
- [Verify: xor-basis.cpp](../../tests/unit/math/xor-basis.cpp)
