## 形式的冪級数の逆関数

`compositional_inverse(f, deg = -1)` は $f(g(x))=x\bmod x^{deg}$ を満たす $g$ を返す。`f[0] = 0`、一次係数 `f[1]` が可逆で、入力長が `2` 以上であることが必要。

配列を渡す版では、内部の `pow_enumerate` が **入力配列の長さ**から計算次数を決める。`deg` と入力長を変えて使わず、先に `f.resize(deg)` してから既定の `deg` で呼ぶ。次数に対応する整数の逆元と NTT 向け FPS バックエンドが必要。

別の版は `compositional_inverse<fps>(calc_f, deg)`。`calc_f(g, d)` が $f(g(x))\bmod x^d$ を返す関数を渡し、Newton 法で逆関数を求める。コールバックは指定次数までの正確な展開を返すこと。

配列版は冪の係数列挙を使い、時間 $O(N\log^2 N)$。コールバック版の時間は合成の計算費用に依存する。

#### 実装・検証

- [実装](../../fps/fps-compositional-inverse.hpp)
- [検証: composition.test.cpp](../../verify/verify-unit-test/composition.test.cpp)
- [検証: yosupo-compositional-inverse-large.test.cpp](../../verify/verify-yosupo-fps/yosupo-compositional-inverse-large.test.cpp)
- [検証: yosupo-compositional-inverse.test.cpp](../../verify/verify-yosupo-fps/yosupo-compositional-inverse.test.cpp)
