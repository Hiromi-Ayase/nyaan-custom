## 任意の法向け FPS バックエンド

`FormalPowerSeries<mint>` の多項式積・逆数・指数関数を、3 素数 NTT による任意法の畳み込みで実装するヘッダ。FPS 本体と一緒に読み込まれる。

- `f *= g` は通常の多項式積。片方が空なら結果も空。
- `f.inv(deg)` は $1/f\bmod x^{deg}$。`f` は非空で定数項が可逆であること。
- `f.exp(deg)` は $\exp(f)\bmod x^{deg}$。定数項は `0`。
- `deg` の省略時は入力の長さ。係数は低次から並べる。

積の長さ・係数上限は `ArbitraryNTT` に従う。対数・指数などでは次数に対応する整数の逆元も必要なので、任意の合成数の法で全演算が使えるわけではない。

`ntt()`, `intt()`, `ntt_doubling()`, `ntt_pr()` は提供されず、呼ぶと `exit(1)` で終了する。これらを直接使うアルゴリズムには NTT 向けバックエンドを選ぶ。`ntt-friendly-fps.hpp` と同時に読み込まない。多項式積が $O(N\log N)$ のとき、逆数・指数も倍精度の Newton 法で準線形時間。

#### 実装・検証

- [実装](../../fps/arbitrary-fps.hpp)
- [検証: yosupo-exp-arb.test.cpp](../../verify/verify-yosupo-fps/yosupo-exp-arb.test.cpp)
- [検証: yosupo-inv-arb.test.cpp](../../verify/verify-yosupo-fps/yosupo-inv-arb.test.cpp)
- [検証: yosupo-log-arb.test.cpp](../../verify/verify-yosupo-fps/yosupo-log-arb.test.cpp)
