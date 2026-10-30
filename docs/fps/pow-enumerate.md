## 多項式の冪から同じ次数の係数を列挙

`pow_enumerate(f, g = {1}, m = -1)` は $[x^n]f(x)^i g(x)$ を `i = 0..m` で列挙する。**`n = f.size()-1`** で、`m` の省略値も `n`。

`f` は非空、`m` は非負とする。特定の次数を抽出したい場合、先に `f` の長さを `n+1` に合わせる。`g` も内部で同じ長さへ切り詰め・ゼロ埋めされる。

NTT、原始根、倍長化の並び順を直接使うので、対応する NTT 向け FPS バックエンドが必要。係数の法は奇素数で、使用する変換長を支えられるものを使う。

`f[0] = 0` では十分大きい `i` の値は `0` になる。この経路の返り値は `pre(m+1)` で切り出すだけなので、`m` を大きく指定しても常に `m+1` 要素が返るとは限らない。必要なら返り値をその長さまでゼロ埋めする。

`m` と `n` が同程度の $N$ なら時間 $O(N\log^2 N)$。任意の `m` を指定した場合は、最後の逆数計算の費用も加わる。

#### 実装・検証

- [実装](../../fps/pow-enumerate.hpp)
- [関連検証（間接使用）: composition.test.cpp](../../verify/verify-unit-test/composition.test.cpp)
- [関連検証（間接使用）: yosupo-compositional-inverse-large.test.cpp](../../verify/verify-yosupo-fps/yosupo-compositional-inverse-large.test.cpp)
- [関連検証（間接使用）: yosupo-compositional-inverse.test.cpp](../../verify/verify-yosupo-fps/yosupo-compositional-inverse.test.cpp)
