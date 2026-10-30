## Auxiliary Tree（Virtual Tree）

`AuxiliaryTree<G>(g,root=0)` は木をコピーして HLD を構築する。`get(vertices)` は指定頂点と必要な LCA だけからなる補助木を返す。

返り値は `(隣接リスト, 元の頂点番号列)`。補助木の辺は親から子への一方向で、番号 i は返却列の i 番目の元頂点に対応する。辺の重みや縮約パス長は含めない。空入力は空の組。

前処理 $O(n)$、k 頂点の問い合わせは $O(k\log k+k\log n)$、出力サイズ $O(k)$。

#### 実装・検証

- [実装](../../tree/auxiliary-tree.hpp)
- [検証: yuki-2588.test.cpp](../../verify/verify-yuki/yuki-2588.test.cpp)
