## 辺を基礎とする Static Top Tree

`DPonStaticTopTree<G,Data,Edge,Compress,Rake>(hld,edge,compress,rake)` は固定木のクラスタ DP を管理する。

`edge(i)` は頂点 i と親の辺に対応する基本情報（根には仮想的な基本情報を用意）。`compress(parent,child)` は縦の結合、`rake(main,side)` は枝の合流を表す。外部データの変更後に `update(i)` で該当辺から再計算し、`get()` で全体の値を取得する。

`StaticTopTree<G>` は `P,L,R,T` の配列で二分木構造を公開する。hld と元の木を生存させ、構造は変えない。

結合が定数時間なら更新 $O(\log n)$、取得 $O(1)$、領域 $O(n)$。構築は保守的に $O(n\log n)$。

#### 実装・検証

- [実装](../../tree/static-top-tree-edge-based.hpp)
