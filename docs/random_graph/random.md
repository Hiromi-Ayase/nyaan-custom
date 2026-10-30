## テスト生成用の乱数生成器

`Random(seed=0)` は splitmix64 で初期化した xoshiro256**。固定シードで再現できる。グローバル `global_gen` も定義する。

`uniform(l,r)` は整数の閉区間、`uniform_bool()` は bool、`uniform01()` は両端を含む実数範囲。`uniform_pair(l,r)` は `l <= a < b <= r`、`lower_string(n)` は英小文字列。

`shuffle(first,last)`, `perm<T>(n)`, `choice(n,l,r)` を提供する。choice は閉区間から重複なく選び昇順に返すが、棄却法なので全域に近い個数を取ると試行が増える。整数の範囲差が型に収まること。

#### 実装・検証

- [実装](../../random_graph/random.hpp)
