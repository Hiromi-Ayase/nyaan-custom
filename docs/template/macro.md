## ループ・入力マクロ

`rep(i,N)` は `[0,N)`、`rep1(i,N)` は `[1,N]`、`reg(i,a,b)` は `[a,b)`。末尾に r を含む `repr`, `repr1`, `regr` は逆順。添字型は long long。

`each/each2` は範囲ループ、`all(v)` は begin/end、`fi/se` は pair のメンバ短縮。`ini/inl/ins` は宣言と入力、`in2/in3/in4` は複数の同サイズ配列を交互に読む。`die(...)` は出力して現在の void 関数から return する。

展開する式の副作用や変数名衝突に注意する。入出力マクロには `Nyaan::in/out` が必要で、通常は `template.hpp` 経由で使う。

#### 実装・検証

- [実装](../../template/macro.hpp)
- [Verify: utilities.cpp](../../tests/unit/template/utilities.cpp)
