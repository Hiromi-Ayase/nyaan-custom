## 複数の多項式の積

`Pi(v)` は多項式の配列 `v` の全要素を掛け合わせる。空配列の積は定数多項式 `{1}`。

隣接する多項式を対にして掛け、要素数を半減させながら処理する。各多項式の係数は低次順で、`fps` の積のバックエンドを用意する。元の `v` は値渡しで変更しない。

次数の合計を $D$、多項式数を $K$ とすると、多項式積の時間を $M(D)$ として $O(M(D)\log K)$ 程度。入力順のまま組み合わせるため、次数の偏りに応じた優先度付きキューでの最適化は行わない。

#### 実装・検証

- [実装](../../fps/fps-utility.hpp)
- [検証: partial-fraction-decomposition.test.cpp](../../verify/verify-unit-test/partial-fraction-decomposition.test.cpp)
- [検証: yosupo-product-of-polynomial-sequence.test.cpp](../../verify/verify-yosupo-fps/yosupo-product-of-polynomial-sequence.test.cpp)
- [検証: yuki-1145.test.cpp](../../verify/verify-yuki/yuki-1145.test.cpp)
