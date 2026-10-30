## Karatsuba 法の多項式積

`karatsuba(a,b)` は低次順の係数列の積を `vector<T>` で返す。係数には加減乗算と零があればよく、根や逆元は不要。

両配列は非空として利用する。現実装は片方だけ空のときの零多項式を通常の空配列として処理しない。長さが小さいときは `KaratsubaImpl::naive` に切り替える。

同程度の長さ $N$ の場合、積を 3 個の半分の問題へ分けて時間 $O(N^{\log_2 3})$、再帰中の追加領域は $O(N)$。整数係数では中間の加減算も含めてオーバーフローしない型を選ぶ。

#### 実装・検証

- [実装](../../ntt/karatsuba.hpp)
- [検証: karatsuba.test.cpp](../../verify/verify-unit-test/karatsuba.test.cpp)
- [検証: yosupo-convolution-2-64-karatsuba.test.cpp](../../verify/verify-yosupo-ntt/yosupo-convolution-2-64-karatsuba.test.cpp)
