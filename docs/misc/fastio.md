## バッファ付き高速入出力

`rd(a,b,...)` は整数（128 bit を含む）・文字・空白区切り文字列を読み込む。`wt(...)` は区切りなしに連結出力し、`wtn(...)` は最後に改行する。空白は `wt(a,' ',b)` のように明示する。

文字列入力は既存の内容へ追記するので、再利用時は clear する。EOF 検出を返す API はなく、必要な入力が存在することを前提とする。出力は終了時に flush されるが、対話処理では `fastio::flush()` を明示する。

`fread/fwrite` と大きな静的バッファを使う。他のバッファ付き入出力との混在を避ける。整数の負号処理では最小の符号付き値の符号反転に注意する。

#### 実装・検証

- [実装](../../misc/fastio.hpp)
- [検証: aoj-2995-hashmap.test.cpp](../../verify/verify-aoj-other/aoj-2995-hashmap.test.cpp)
- [検証: aoj-2995.test.cpp](../../verify/verify-aoj-other/aoj-2995.test.cpp)
- [検証: yosupo-dynamic-sequence-range-affine-range-sum-splay.test.cpp](../../verify/verify-yosupo-ds/yosupo-dynamic-sequence-range-affine-range-sum-splay.test.cpp)
