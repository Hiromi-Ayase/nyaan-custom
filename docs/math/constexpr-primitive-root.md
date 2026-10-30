## constexpr 原始根探索

`constexpr_primitive_root(unsigned int mod)` は素数 mod の原始根を求める。2 なら 1。mod-1 を試し割りで分解し、小さい候補から検査する。

入力の素数性を保証し、mod>=2 とする。定数式で評価できるが、大きな法ではコンパイラの constexpr 計算量上限に達し得る。試し割りは $O(\sqrt{mod})$、さらに候補の累乗判定を行う。

#### 実装・検証

- [実装](../../math/constexpr-primitive-root.hpp)
- [検証: primitive-root.test.cpp](../../verify/verify-unit-test/primitive-root.test.cpp)
- [検証: yuki-1783.test.cpp](../../verify/verify-yuki/yuki-1783.test.cpp)
