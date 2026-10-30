## 凸性を利用する min-plus / max-plus 畳み込み

`concave_min_plus_convolution(a,b)` は `c[k] = min(a[i]+b[j])`（`i+j=k`）を返す。名前にかかわらず `a` は下に凸、すなわち隣接差が非減少であることが必要。`b` は任意。

`concave_max_plus_convolution` は max 版で、`a` の隣接差が非増加であることが必要。長さは `a.size()+b.size()-1`、どちらかが空なら空。

Monotone Minima を使用し、長さを $n,m$ とすると時間 $O((n+m)\log(n+m))$、領域 $O(n+m)$。

#### 実装・検証

- [実装](../../dp/concave-min-plus-convolution.hpp)
- [検証: yosupo-concave-min-plus-convolution-1.test.cpp](../../verify/verify-yosupo-math/yosupo-concave-min-plus-convolution-1.test.cpp)
- [検証: yosupo-concave-min-plus-convolution-2.test.cpp](../../verify/verify-yosupo-math/yosupo-concave-min-plus-convolution-2.test.cpp)
