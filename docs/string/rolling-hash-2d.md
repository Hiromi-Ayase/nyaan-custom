## 二次元Rolling Hash

二次元の列の一致判定を前計算$\mathrm{O}(n)$クエリ$\mathrm{O}(1)$で処理するライブラリ。

#### 使い方

- `RollingHash2D<Str>(S)`: コンストラクタ。Sを対象としたRollingHashを構築する。$\mathrm{O}(\lvert S\rvert)$
- `build(S)`: Sを対象としたRollingHashを構築する。行数・幅を変えて繰り返し呼べる。$\mathrm{O}(\lvert S\rvert)$
- `get(u, l, d, r)`: 行 `[u,d)`、列 `[l,r)` の矩形のハッシュを返す。$\mathrm{O}(1)$
- `get_hash(T)`: Tのハッシュ値を返す。$\mathrm{O}(\lvert T\rvert)$

各行の長さは同じにする。デフォルト構築と空入力は高さ・幅とも0の行列を表す。空矩形のハッシュは0。

#### 実装・検証

- [実装](../../string/rolling-hash-2d.hpp)
- [Verify: rolling-hash-2d.cpp](../../tests/unit/string/rolling-hash-2d.cpp)
