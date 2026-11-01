## 永続配列

`PersistentArray<T,shift=4>(MAX,ID)` は非負添字の配列を多分木で管理する。未設定値は `ID`。配列を渡して初期化することもできる。

- `get(k)` / `get(root,k)`: 現在版・指定版の値。
- `update(k,x)` / `update(root,k,x)`: 指定版から一点を変更し、新しい根を返す。同時にメンバ `root` も変更する。旧版の根は有効なまま。

`MAX > 0` とし、添字は構築時に確保した桁数に収める。デフォルトコンストラクタだけでは未初期化。分岐数 $B=2^{shift}$、深さ $D$ に対し取得は $O(D)$、更新は子配列のコピーを含め $O(BD)$、追加領域も $O(BD)$。節点の自動解放は行わない。

#### 実装・検証

- [実装](../../data-structure/persistent-array.hpp)
- [Verify: persistent.cpp](../../tests/unit/data-structure/persistent.cpp)
