## XOR 線形基底

`Basis<Int,MAX>` は下位 MAX ビットの XOR 線形空間を管理する。Int は 64 bit 以下の非負整数として扱う。

`add(x)` は独立な基底が増えたかを返す。`test(x)` は生成可能性、`get_max()` は生成可能な最大値、`size()` は次元。`merge(rhs)` は空間の和、`get_basis()` は正規化した基底、`orthogonal_complement(N=MAX)` は N ビット空間内の直交補空間。

追加・判定 $O(MAX)$、正規化・併合・補空間は $O(MAX^2)$、領域 $O(MAX)$。

#### 実装・検証

- [実装](../../math/sweep.hpp)
- [検証: aoj-3277.test.cpp](../../verify/verify-aoj-other/aoj-3277.test.cpp)
