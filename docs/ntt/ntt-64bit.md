## 64 bit の法での数論変換

`NTT_64bit<mint>` は 64 bit の素数の法に対応する NTT。構築時に `mint::get_mod()` と原始根を取得するので、動的 modint の法は構築前に設定し、その後変更しない。

`ntt(a)` と正規化済みの `intt(a)`、通常の畳み込み `multiply(a,b)`、変換済み配列の `ntt_doubling(a)` を提供する。畳み込みは非空入力を渡す。

変換長は法の `p-1` を割り切る 2 冪。内部表の初期化には `v2(p-1) >= 3` の法を使い、長さは実装中の `int` とシフトで表せる範囲に収める。64 bit の法を使えても、配列長が 64 bit 全域になるわけではない。

時間 $O(N\log N)$、領域 $O(N)$ に、構築時の原始根探索の費用が加わる。

#### 実装・検証

- [実装](../../ntt/ntt-64bit.hpp)
- [検証: ntt-64bit.test.cpp](../../verify/verify-unit-test/ntt-64bit.test.cpp)
