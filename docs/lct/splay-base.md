## Splay Tree の基底

`SplayTreeBase<Node>` は `l,r,p,key,cnt` を持つ節点に対する回転・列の結合分割を提供する。派生クラスは `push` と `update` を実装する。

`my_new/my_del` は節点管理、`splay(node)` は補助木の根への移動。`split(root,k)`, `merge(left,right)`, `build(v)`, `insert/erase(root,k)` は列操作。Link/Cut Tree の親ポインタも考慮した `is_root` を使う。

根と節点の所有権は呼び出し側で管理する。Splay 操作には償却解析が必要で、再帰的な split を含む単発操作の最悪時間は $O(n)$。

#### 実装・検証

- [実装](../../lct/splay-base.hpp)
- [Verify: splay-sequences.cpp](../../tests/unit/lct/splay-sequences.cpp)
