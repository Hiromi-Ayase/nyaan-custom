## ハッシュ構造体

$2^{61}-1$ を法とするハッシュのライブラリ。

ハッシュは単位的環としていて実装されている。また、ハッシュに $\mathbb{Z} / (2^{61} - 1) \mathbb{Z}$ 上の要素を作用させることもできる。

#### 関数

- `Hash set(long long a)`: `a`に対応するハッシュを生成。
- `Hash get_basis()`: ランダムなハッシュを生成。(要素は原始根であることが保証される。)
- `+,-,*,+=,-=,*=`: 加算・減算・乗算用の関数。
- `Hash pfma(Hash a, Hash b, T c)`: `fma` 用の関数。`T` は` hash` または `long long` 。

#### 実装・検証

- [実装](../../internal/internal-hash.hpp)
- [検証: inner-hash.test.cpp](../../verify/verify-unit-test/inner-hash.test.cpp)
