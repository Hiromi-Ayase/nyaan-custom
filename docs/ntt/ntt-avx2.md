## AVX2 による数論変換

`NTT<mint>` は Montgomery modint の内部表現を AVX2 でまとめて処理する。対応する 32 bit Montgomery modint と AVX2 対応 CPU が必要。

`ntt(a)`、正規化済みの `intt(a)`、`multiply(a,b)`、`ntt_doubling(a)` を提供する。ポインタと長さを受け取る低水準 API もあるが、通常はベクトル版を使う。畳み込みでは両入力を非空にする。

変換長は 2 冪で、法の `p-1` を割り切り、かつ固定バッファ容量 `1<<23` 以下である必要がある。内部表は十分な 2 冪因子を持つ法（`v2(p-1) >= 3`）を前提とする。倍長化では結果の長さも条件内に収める。

時間 $O(N\log N)$。固定の変換バッファを共有するため、複数インスタンスでも並行呼び出しはできない。他の `NTT` 実装と同じ翻訳単位に読み込まない。

#### 実装・検証

- [実装](../../ntt/ntt-avx2.hpp)
- [Verify: ntt-avx2.cpp](../../tests/unit/ntt/ntt-avx2.cpp)
