## iostream 入出力補助

`Nyaan::in(a,b,...)` は順に入力し、`out(a,b,...)` は空白区切りで出力して改行する。pair・既存サイズの vector・128 bit 整数のストリーム演算を追加する。vector のサイズは読み込まない。

静的初期化で `cin.tie(nullptr)`、同期無効化、cout の小数精度 15 桁・cerr 7 桁を設定する。C の stdio と混在させない。符号付き最小値の出力は内部の符号反転に注意する。

必要な標準ヘッダは `template.hpp` が先に用意する。

#### 実装・検証

- [実装](../../template/inout.hpp)
- [関連検証（間接使用）: verify-aoj-alds-14-c.test.cpp](../../verify/verify-aoj-alds/verify-aoj-alds-14-c.test.cpp)
- [関連検証（間接使用）: aoj-cgl-1-a.test.cpp](../../verify/verify-aoj-cgl/aoj-cgl-1-a.test.cpp)
- [関連検証（間接使用）: aoj-cgl-1-b.test.cpp](../../verify/verify-aoj-cgl/aoj-cgl-1-b.test.cpp)
